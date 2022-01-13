#pragma once
#include <irrlicht.h>
#include "Ship.h"

#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

enum {
	PLAYER_CAMERA,
	PLAYER_SHIP_NODE,
	PLAYER_MESH
};

class Controller;
struct MouseStateMap;

class PlayerShip : public Ship
{
public:
	PlayerShip(IAnimatedMesh* ship, IAnimatedMeshSceneNode* node, ICameraSceneNode* camera, Controller* cont);
	PlayerShip();
	virtual void update(f32 time);
	ICameraSceneNode* camera;
	//REMOVE THIS LATER
	ISceneNode* mousePointer;
	//REMOVE THIS LATER

protected:

};

#endif
