#include "SceneManager.h"
#include "Controller.h"


void SceneManager::update(f32 time)
{
	dt = time;
	shipMovementSystem(scene, dt); //updates impulses based on player input
	weaponFiringSystem(scene, controller->bulletWorld, controller, dt); //fires guns
	controller->bulletWorld->stepSimulation(dt, 60); //applies the PHYSICS
	irrlichtRigidBodyPositionSystem(scene, dt); //updates position based on rigidbody state
	projectileRangeSystem(controller->bulletWorld, scene);
	playerUpdateSystem(scene, dt); //updates camera location
}

