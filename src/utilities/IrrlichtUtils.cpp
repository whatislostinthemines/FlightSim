#include "IrrlichtUtils.h"
#include <string>

vector3df getNodeForward(ISceneNode* node)
{
	return node->getAbsoluteTransformation().getRotationDegrees().rotationToDirection(vector3df(0, 0, 1));
}

vector3df getNodeBackward(ISceneNode* node)
{
	return -getNodeForward(node);
}

vector3df getNodeUp(ISceneNode* node)
{
	return node->getAbsoluteTransformation().getRotationDegrees().rotationToDirection(vector3df(0, 1, 0));
}

vector3df getNodeDown(ISceneNode* node)
{
	return -getNodeUp(node);
}

vector3df getNodeRight(ISceneNode* node)
{
	return node->getAbsoluteTransformation().getRotationDegrees().rotationToDirection(vector3df(1, 0, 0));
}

vector3df getNodeLeft(ISceneNode* node)
{
	return -getNodeRight(node);
}

EntityId strToId(std::string id)
{
	return std::stoull(id);
}
std::string idToStr(EntityId id)
{
	return std::to_string(id);
}