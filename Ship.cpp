#include "Ship.h"
#include "FlightEventReceiver.h"
#include <iostream>
#include <cmath>

Ship::Ship(IAnimatedMesh* nship, IAnimatedMeshSceneNode* nnode, Controller* cont, f32 mass, f32 inertia)
{
	controller = cont;
	ship = nship;
	node = nnode;
	velocity = vector3df(0, 0, 0);
	force = vector3df(0, 0, 0);
	torque = vector3df(0, 0, 0);
	rotVelocity = vector3df(0, 0, 0);
	rigidBodyComponent = {
		vector3df(),
		quaternion(node->getRotation() * DEGTORAD),
		node->getPosition(),
		vector3df(),
		quaternion(),
		vector3df(),
		vector3df(),
		mass,
		1/mass,
		inertia,
		1/inertia
	};
}

Ship::Ship()
{
	controller = 0;
	ship = 0;
	node = 0;
	velocity = vector3df(0, 0, 0);
	force = vector3df(0, 0, 0);
	torque = vector3df(0, 0, 0);
	rotVelocity = vector3df(0, 0, 0);
	rigidBodyComponent = {
		vector3df(),
		quaternion(0,1,0,0),
		vector3df(),
		vector3df(),
		quaternion(),
		vector3df(),
		vector3df()
	};
}

//returns a normalized vector for the forward position
vector3df Ship::getForward()
{
	if (node) {
		vector3df rotation = node->getRotation();
		vector3df forward = vector3df(0, 0, -1);
		return rotation.rotationToDirection(forward);
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
		vector3df rotation = node->getRotation();
		vector3df left = vector3df(1, 0, 0);
		return rotation.rotationToDirection(left);
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
		vector3df rotation = node->getRotation();
		vector3df up = vector3df(0, 1, 0);
		return rotation.rotationToDirection(up);
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
	vector3df impulse = force * time;
	Physics::applyImpulse(&rigidBodyComponent, impulse);

	node->setPosition(rigidBodyComponent.position);
	force = vector3df();
	
	vector3df angularImpulse = torque * time;
	Physics::applyAngularImpulse(&rigidBodyComponent, angularImpulse);
	vector3df eulerOrientation = vector3df();
	rigidBodyComponent.orientation.toEuler(eulerOrientation);
	eulerOrientation = eulerOrientation * RADTODEG;
	node->setRotation(eulerOrientation);
	torque = vector3df();
	/*
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
	*/
}

void Ship::accelerateForward()
{
	force += (getForward() * maxSpeed);
}

void Ship::accelerateBackward()
{

	force += (getBackward() * maxSpeed);
}

void Ship::strafeLeft()
{
	force += (getLeft() * maxSpeed);
}

void Ship::strafeRight()
{
	force += (getRight() * maxSpeed);
}

void Ship::strafeUp()
{
	force += (getUp() * maxSpeed);
}

void Ship::strafeDown()
{
	force += (getDown() * maxSpeed);
}

//rotations
void Ship::yawLeft()
{
	torque.Y -= maxRotSpeed - rigidBodyComponent.angularVelocity.Y;
}

void Ship::yawRight()
{
	torque.Y +=  maxRotSpeed - rigidBodyComponent.angularVelocity.Y;
}

void Ship::pitchUp()
{
	torque.X += maxRotSpeed - rigidBodyComponent.angularVelocity.X;
}

void Ship::pitchDown()
{
	torque.X -= maxRotSpeed - rigidBodyComponent.angularVelocity.X;
}
void Ship::rollLeft()
{
	torque.Z -= maxRotSpeed - rigidBodyComponent.angularVelocity.Z;
}
void Ship::rollRight()
{
	torque.Z += maxRotSpeed - rigidBodyComponent.angularVelocity.Z;
}

void Ship::stopMoving()
{
	torque += (-rigidBodyComponent.angularVelocity) * maxRotSpeed;
	force += (-rigidBodyComponent.velocity * maxSpeed);
}