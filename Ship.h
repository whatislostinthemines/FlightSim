#pragma once
#include <irrlicht.h>
#include "Physics.h"

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
		Ship(IAnimatedMesh* ship, IAnimatedMeshSceneNode* node, Controller* cont, f32 mass, f32 inertia);
		Ship();
		virtual void update(f32 time);
		void posUpdate(f32 time);
		IAnimatedMesh* ship;
		IAnimatedMeshSceneNode* node;
		Controller* controller;
		RigidBodyComponent rigidBodyComponent;

		vector3df getForward();
		vector3df getBackward();
		vector3df getLeft();
		vector3df getRight();
		vector3df getUp();
		vector3df getDown();

	protected:
		f32 maxSpeed = 40.f;
		f32 maxRotSpeed = 10.f;

		vector3df velocity;
		vector3df force;
		vector3df torque;
		vector3df rotVelocity;

		virtual void accelerateForward();
		virtual void accelerateBackward();
		virtual void strafeLeft();
		virtual void strafeRight();
		virtual void strafeUp();
		virtual void strafeDown();
		virtual void pitchUp();
		virtual void pitchDown();
		virtual void rollLeft();
		virtual void rollRight();
		virtual void yawLeft();
		virtual void yawRight();
		virtual void stopMoving();
		virtual void turnToPos(vector3df pos);

};
#endif 
