#include "Ship.h"
#include "Controller.h"
#include <iostream>
#include <cmath>

Ship::Ship(IAnimatedMesh* nship, IAnimatedMeshSceneNode* nnode, f32 mass, f32 inertia, Controller* cont) : RigidPhysicsObject(nship, nnode, mass, inertia, cont)
{

	//very basic hardpoint setup with terrible laser model
	hardpoints[0] = vector3df(2.4816f, .25f, -6.0088f);
	hardpoints[1] = vector3df(-2.4816f, .25f, -6.0088f);
	IMesh* wepMesh = controller->smgr->getMesh("models/wazer/wazer.obj");
	IMeshSceneNode* wepNode1 = controller->smgr->addMeshSceneNode(wepMesh, node, -1, hardpoints[0], vector3df(0, 0, 0), vector3df(.5f, .5f, .5f));
	IMeshSceneNode* wepNode2 = controller->smgr->addMeshSceneNode(wepMesh, node, -1, hardpoints[1], vector3df(0, 0, 0), vector3df(.5f, .5f, .5f));
	weapons[0] = new Weapon(wepNode1, wepMesh, controller);
	weapons[1] = new Weapon(wepNode2, wepMesh, controller);
}

Ship::Ship() : RigidPhysicsObject()
{
	weapons[0] = 0;
	weapons[1] = 0;
}

void Ship::update(f32 time)
{
	//no matter what else goes in here, call posUpdate at the end of the update
	posUpdate(time);
}


void Ship::fireWeapons(f32 time)
{
	for (int i = 0; i < 2; ++i) {
		weapons[i]->fire(time);
	}
}

void Ship::accelerateForward()
{
	force += (getForward() * maxSpeed);
}

void Ship::accelerateBackward()
{

	force += (getBackward() * maxSpeed);
}

void Ship::strafeLeft()
{
	force += (getLeft() * maxSpeed);
}

void Ship::strafeRight()
{
	force += (getRight() * maxSpeed);
}

void Ship::strafeUp()
{
	force += (getUp() * maxSpeed);
}

void Ship::strafeDown()
{
	force += (getDown() * maxSpeed);
}

//rotations
void Ship::yawLeft()
{
	torque.Y -= maxRotSpeed + rigidBodyComponent.angularVelocity.Y;
}

void Ship::yawRight()
{
	torque.Y +=  maxRotSpeed - rigidBodyComponent.angularVelocity.Y;
}

void Ship::pitchUp()
{
	torque.X -= maxRotSpeed + rigidBodyComponent.angularVelocity.X;
}

void Ship::pitchDown()
{
	torque.X += maxRotSpeed - rigidBodyComponent.angularVelocity.X;
}
void Ship::rollLeft()
{
	torque.Z += maxRotSpeed - rigidBodyComponent.angularVelocity.Z;
}
void Ship::rollRight()
{
	torque.Z -= maxRotSpeed + rigidBodyComponent.angularVelocity.Z;
}

void Ship::stopMoving()
{
	torque += (-rigidBodyComponent.angularVelocity) * maxRotSpeed;
	force += (-rigidBodyComponent.velocity * maxSpeed);
}
