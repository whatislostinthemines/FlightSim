#pragma once
#include <irrlicht.h>
#include "Physics.h"
#include "Weapons.h"

#ifndef SHIP_H
#define SHIP_H

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

class Controller;

class Ship
{
	public:
		Ship(IAnimatedMesh* ship, IAnimatedMeshSceneNode* node, f32 mass, f32 inertia, Controller* cont);
		Ship();
		virtual void update(f32 time);
		void posUpdate(f32 time);
		IAnimatedMesh* ship;
		IAnimatedMeshSceneNode* node;
		RigidBodyComponent rigidBodyComponent;
		Controller* controller;

		vector3df hardpoints[2];
		Weapon* weapons[2];

		vector3df getForward();
		vector3df getBackward();
		vector3df getLeft();
		vector3df getRight();
		vector3df getUp();
		vector3df getDown();

		void accelerateForward();
		void accelerateBackward();
		void strafeLeft();
		void strafeRight();
		void strafeUp();
		void strafeDown();
		void pitchUp();
		void pitchDown();
		void rollLeft();
		void rollRight();
		void yawLeft();
		void yawRight();
		void stopMoving();
		void turnToPos(vector3df pos);
		void fireWeapons(f32 time);

	protected:
		f32 maxSpeed = 40.f;
		f32 maxRotSpeed = 10.f;

		vector3df velocity;
		vector3df force;
		vector3df torque;
		vector3df rotVelocity;

};
#endif 
