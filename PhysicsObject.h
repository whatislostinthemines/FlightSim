#pragma once
#include <irrlicht.h>
#include "Physics.h"

#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

class Controller;

class RigidPhysicsObject 
{
	public:
		RigidPhysicsObject(IAnimatedMesh* nmesh, IAnimatedMeshSceneNode* nnode, f32 mass, f32 inertia, Controller* cont);
		RigidPhysicsObject();

		void posUpdate(f32 time);

		IAnimatedMesh* mesh;
		IAnimatedMeshSceneNode* node;
		RigidBodyComponent rigidBodyComponent;
		Controller* controller;

		vector3df getForward();
		vector3df getBackward();
		vector3df getLeft();
		vector3df getRight();
		vector3df getUp();
		vector3df getDown();

		void turnToPos(vector3df pos);

	protected:
		f32 maxSpeed = 40.f;
		f32 maxRotSpeed = 10.f;

		vector3df velocity;
		vector3df force;
		vector3df torque;
		vector3df rotVelocity;
};

#endif