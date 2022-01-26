#pragma once
#ifndef IRRLICHTCOMPONENT_H
#define IRRLICHTCOMPONENT_H
#include "BaseHeader.h"

struct IrrlichtComponent {
	ISceneNode* node;
	vector3df getForward();
	vector3df getBackward();
	vector3df getLeft();
	vector3df getRight();
	vector3df getUp();
	vector3df getDown();
};

#endif