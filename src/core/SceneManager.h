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
#include "GameDefaults.h"

class Controller;

class SceneManager {
	public:
		SceneManager(Scene scene, Controller* controller, btDiscreteDynamicsWorld* bulletWorld) : controller(controller), scene(scene), bulletWorld(bulletWorld) {}
		SceneManager() : controller(0), bulletWorld(0) {} 
		void update(f32 dt);
		f32 dt = 0;
		Scene scene;
		Controller* controller;
		btDiscreteDynamicsWorld* bulletWorld;
		GameDefaults defaults;
};

#endif