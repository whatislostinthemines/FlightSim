#pragma once

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "ECS.h"
#include <irrlicht.h>
#include "ShipMovementSystem.h"
#include "IrrlichtRigidBodyPositionSystem.h"
#include "PlayerUpdateSystem.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

class Controller;

class SceneManager {
	public:
		SceneManager(Scene scene, Controller* controller) : controller(controller), scene(scene) {}
		SceneManager() : controller(0) {} 
		void update(f32 dt);
		f32 dt = 0;
		Scene scene;
		Controller* controller;

};

#endif