#pragma once
#include <irrlicht.h>
#include "Ship.h"
#include "CameraRig.h"

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

class Player
{
public:
	Player(Ship* pship, ICameraSceneNode* camera, Controller* cont);
	Player();
	virtual void update(f32 time);
	CameraRig camRig;
	Controller* controller;
	Ship* ship;

protected:
	f32 sensitivity = .001f;
};

#endif
