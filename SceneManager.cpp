#include "SceneManager.h"
#include "Controller.h"


void SceneManager::update(f32 time)
{
	dt = time;
	shipMovementSystem(scene, dt); //updates impulses based on player input
	weaponFiringSystem(scene, controller->bulletWorld, controller, dt); //fires guns
	controller->bulletWorld->stepSimulation(dt, 60); //applies the PHYSICS
	collisionCheckingSystem(controller->bulletWorld, scene); //destroys projectiles on hit
	updateHealthSystem(controller->bulletWorld, scene); //updates health and removes objects with no health
	irrlichtRigidBodyPositionSystem(scene, dt); //updates position based on rigidbody state
	projectileRangeSystem(controller->bulletWorld, scene); //kills projectiles after they have gone a set distance
	playerUpdateSystem(scene, dt); //updates camera location
}

