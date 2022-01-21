#pragma once
#include <irrlicht.h>
#ifndef IRRLICHTCOMPONENT_H
#define IRRLICHTCOMPONENT_H
using namespace irr;
using namespace scene;
using namespace core;

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