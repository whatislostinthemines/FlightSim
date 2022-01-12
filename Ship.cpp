#include "Ship.h"
#include "FlightEventReceiver.h"
#include <iostream>
#include <cmath>

Ship::Ship(IAnimatedMesh* nship, IAnimatedMeshSceneNode* nnode, Controller* cont)
{
	controller = cont;
	ship = nship;
	node = nnode;
	velocity = vector3df(0, 0, 0);
	force = vector3df(0, 0, 0);
	rotForce = vector3df(0, 0, 0);
	rotVelocity = vector3df(0, 0, 0);
}

Ship::Ship()
{
	controller = 0;
	ship = 0;
	node = 0;
	velocity = vector3df(0, 0, 0);
	force = vector3df(0, 0, 0);
	rotForce = vector3df(0, 0, 0);
	rotVelocity = vector3df(0, 0, 0);
}

//returns a normalized vector for the forward position
vector3df Ship::getForward()
{
	if (node) {
		matrix4 mat = node->getRelativeTransformation();
		return vector3df(-mat[8], -mat[9], -mat[10]).normalize();
	}
	return vector3df(0, 0, 0);
}

vector3df Ship::getBackward()
{
	return -getForward();
}

vector3df Ship::getLeft()
{
	if (node) {
		matrix4 mat = node->getRelativeTransformation();
		return vector3df(mat[0], mat[1], mat[2]).normalize();
	}
	return vector3df(0, 0, 0);
}

vector3df Ship::getRight()
{
	return -getLeft();
}

vector3df Ship::getUp()
{
	if (node) {
		matrix4 mat = node->getRelativeTransformation();
		return vector3df(mat[4], mat[5], mat[6]).normalize();
	}
	return vector3df(0, 0, 0);
}

vector3df Ship::getDown()
{
	return -getUp();

}
void Ship::update(f32 time)
{
}

vector3df rotateAxes(vector3df oldRot, vector3df rotAngles)
{
	matrix4 transform;
	transform.setRotationDegrees(oldRot);
	vector3df axisX(1, 0, 0), axisY(0, 1, 0), axisZ(0, 0, 1);
	matrix4 matRotX, matRotY, matRotZ;

	transform.rotateVect(axisX);
	transform.rotateVect(axisY);
	transform.rotateVect(axisZ);

	matRotX.setRotationAxisRadians(rotAngles.X * DEGTORAD, axisX);
	matRotY.setRotationAxisRadians(rotAngles.Y * DEGTORAD, axisY);
	matRotZ.setRotationAxisRadians(rotAngles.Z * DEGTORAD, axisZ);

	matrix4 newTransform = matRotX * matRotY * matRotZ * transform;
	return newTransform.getRotationDegrees();
}

void Ship::posUpdate(f32 time)
{
	vector3df rotFrictionVelocity = -rotVelocity;
	//position
	vector3df acceleration = force / mass;
	if (acceleration.getLength() > 0) {
		acceleration = acceleration.normalize() * std::min(acceleration.getLength(), maxForce);
	}
	velocity += acceleration * time;
	if (velocity.getLength() > 0) {
		velocity = velocity.normalize() * std::min(velocity.getLength(), maxSpeed);
	}
	vector3df pos = node->getPosition() + (velocity * time);

	//rotation
	vector3df rotAcceleration = rotForce / mass;

	if (rotAcceleration.getLength() > 0) {
		rotAcceleration = rotAcceleration.normalize() * std::min(rotAcceleration.getLength(), maxRotForce);
	}
	rotVelocity += rotAcceleration * time;

	//space friction
	rotVelocity += rotFriction * rotFrictionVelocity * time;

	if (rotVelocity.getLength() > 0) {
		rotVelocity = rotVelocity.normalize() * std::min(rotVelocity.getLength(), maxRotSpeed);
	}

	vector3df deltaV = rotVelocity * time;
	vector3df rot = rotateAxes(node->getRotation(), deltaV);


	if (rot.X > 360) rot.X -= 360;
	else if (rot.X < -360) rot.X += 360;

	if (rot.Y > 360) rot.Y -= 360;
	else if (rot.Y < -360) rot.Y += 360;

	if (rot.Z > 360) rot.Z -= 360;
	else if (rot.Z < -360) rot.Z += 360;

	node->setPosition(pos);
	node->setRotation(rot);

	force = vector3df(0, 0, 0);
	rotForce = vector3df(0, 0, 0);
}

void Ship::accelerateForward()
{
	force += (getForward() * maxSpeed) - velocity;
}

void Ship::accelerateBackward()
{
	force += (getBackward() * maxSpeed) - velocity;
}

void Ship::strafeLeft()
{
	force += (getLeft() * maxSpeed) - velocity;
}

void Ship::strafeRight()
{
	force += (getRight() * maxSpeed) - velocity;
}

void Ship::strafeUp()
{
	force += (getUp() * maxSpeed) - velocity;
}

void Ship::strafeDown()
{
	force += (getDown() * maxSpeed) - velocity;
}

//rotations
void Ship::yawLeft()
{
	rotForce.Y -= maxRotSpeed - rotVelocity.Y;
}

void Ship::yawRight()
{
	rotForce.Y +=  maxRotSpeed - rotVelocity.Y;
}

void Ship::pitchUp()
{
	rotForce.X += maxRotSpeed - rotVelocity.X;
}

void Ship::pitchDown()
{
	rotForce.X -= maxRotSpeed - rotVelocity.X;
}
void Ship::rollLeft()
{
	rotForce.Z -= maxRotSpeed - rotVelocity.Z;
}
void Ship::rollRight()
{
	rotForce.Z += maxRotSpeed - rotVelocity.Z;
}

void Ship::stopMoving()
{
	rotForce += (-rotVelocity * maxRotSpeed);
	force += (-velocity * maxSpeed);
}