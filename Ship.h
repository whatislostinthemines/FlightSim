#pragma once
#include <irrlicht.h>

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
vector3df rotateAxes(vector3df oldRot, vector3df rotAngles);
class Ship
{
	public:
		Ship(IAnimatedMesh* ship, IAnimatedMeshSceneNode* node, Controller* cont);
		Ship();
		virtual void update(f32 time);
		void posUpdate(f32 time);
		IAnimatedMesh* ship;
		IAnimatedMeshSceneNode* node;
		Controller* controller;

		vector3df getForward();
		vector3df getBackward();
		vector3df getLeft();
		vector3df getRight();
		vector3df getUp();
		vector3df getDown();

	protected:
		f32 maxSpeed = 40.f;
		f32 maxRotSpeed = 160.f;
		f32 maxForce = 60.f;
		f32 maxRotForce = 160.f;

		f32 rotFriction = 0.4f;

		vector3df velocity;
		vector3df force;
		vector3df rotForce;
		vector3df rotVelocity;
		f32 mass = 1;

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

};
#endif 
