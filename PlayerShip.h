#pragma once
#include <irrlicht.h>

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

class PlayerShip
{
public:
	PlayerShip(IAnimatedMesh* ship, IAnimatedMeshSceneNode* node, ICameraSceneNode* camera, Controller* cont);
	PlayerShip();
	void update(f32 time);
	IAnimatedMesh* ship;
	IAnimatedMeshSceneNode* node;
	ICameraSceneNode* camera;
private:
	Controller* controller;
	f32 speed = 10.f;
	f32 rotspeed = 20.f;
};

#endif
