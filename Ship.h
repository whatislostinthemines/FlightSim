#pragma once
#include <irrlicht.h>
#include "Physics.h"
#include "PhysicsObject.h"
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

class Ship : public RigidPhysicsObject
{
	public:
		Ship(IAnimatedMesh* ship, IAnimatedMeshSceneNode* node, f32 mass, f32 inertia, Controller* cont);
		Ship();

		virtual void update(f32 time);

		vector3df hardpoints[2];
		Weapon* weapons[2];

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

		void fireWeapons(f32 time);

	protected:

};

#endif 
