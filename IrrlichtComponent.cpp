#include "IrrlichtComponent.h"

vector3df IrrlichtComponent::getForward()
{
	if (node) {
		vector3df rotation = node->getRotation();
		vector3df forward = vector3df(0, 0, 1);
		return rotation.rotationToDirection(forward);
	}
	return vector3df(0, 0, 0);
}

vector3df IrrlichtComponent::getBackward()
{
	return -getForward();
}

vector3df IrrlichtComponent::getRight()
{
	if (node) {
		vector3df rotation = node->getRotation();
		vector3df left = vector3df(1, 0, 0);
		return rotation.rotationToDirection(left);
	}
	return vector3df(0, 0, 0);
}

vector3df IrrlichtComponent::getLeft()
{
	return -getRight();
}

vector3df IrrlichtComponent::getUp()
{
	if (node) {
		vector3df rotation = node->getRotation();
		vector3df up = vector3df(0, 1, 0);
		return rotation.rotationToDirection(up);
	}
	return vector3df(0, 0, 0);
}

vector3df IrrlichtComponent::getDown()
{
	return -getUp();
}