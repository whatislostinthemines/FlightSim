#include "Ship.h"
#include "FlightEventReceiver.h"
#include <iostream>

Ship::Ship(IAnimatedMesh* nship, IAnimatedMeshSceneNode* nnode, Controller* cont)
{
	controller = cont;
	ship = nship;
	node = nnode;
	velocity = vector3df(0, 0, 0);
}

Ship::Ship()
{
	controller = 0;
	ship = 0;
	node = 0;
	velocity = vector3df(0, 0, 0);
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
	vector3df newpos = node->getPosition() + (velocity * time);
	node->setPosition(newpos);
	if (velocity.getLength() > 0) {
		velocity = velocity.normalize()*std::min(velocity.getLength(), maxspeed);
	}
}

void Ship::accelerateForward()
{
	velocity += getForward() * maxspeed;
}

void Ship::accelerateBackward()
{
	velocity += getBackward() * maxspeed;
}

void Ship::strafeLeft()
{
	velocity += getLeft() * maxspeed;
}

void Ship::strafeRight()
{
	velocity += getRight() * maxspeed;
}

void Ship::strafeUp()
{
	velocity += getUp() * maxspeed;
}

void Ship::strafeDown()
{
	velocity += getDown() * maxspeed;
}