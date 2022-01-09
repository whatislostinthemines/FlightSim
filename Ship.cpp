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

void Ship::posUpdate(f32 time)
{
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
	if (rotVelocity.getLength() > 0) {
		rotVelocity = rotVelocity.normalize() * std::min(rotVelocity.getLength(), maxSpeed);
	}

	vector3df rot = node->getRotation() + (rotVelocity * time);

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

void Ship::yawLeft()
{
	rotForce += (getDown() * maxRotSpeed) - rotVelocity;
}

void Ship::yawRight()
{
	rotForce += (getUp() * maxRotSpeed) - rotVelocity;
}

void Ship::pitchUp()
{
	rotForce += (getLeft() * maxRotSpeed) - rotVelocity;
}

void Ship::pitchDown()
{
	rotForce += (getRight() * maxRotSpeed) - rotVelocity;
}
void Ship::rollLeft()
{
	rotForce += (getForward() * maxRotSpeed) - rotVelocity;
}
void Ship::rollRight()
{
	rotForce += (getBackward() * maxRotSpeed) - rotVelocity;
}