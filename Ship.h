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
		f32 maxspeed = 10.f;
		f32 rotspeed = 20.f;
		vector3df velocity;
		void accelerateForward();
		void accelerateBackward();
		void strafeLeft();
		void strafeRight();
		void strafeUp();
		void strafeDown();

};
#endif 
