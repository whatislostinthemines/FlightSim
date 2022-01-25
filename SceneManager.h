#pragma once

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "BaseHeader.h"

#include "ECS.h"
#include "ShipMovementSystem.h"
#include "IrrlichtRigidBodyPositionSystem.h"
#include "PlayerUpdateSystem.h"
#include "WeaponFiringSystem.h"
#include "CollisionCheckingSystem.h"
#include "HealthSystem.h"

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