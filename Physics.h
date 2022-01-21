#pragma once
#include <irrlicht.h>
#include <vector>
#include "ECS.h"


#ifndef PHYSICS_H
#define PHYSICS_H

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif
using namespace irr;
using namespace core;
using namespace std;

struct RigidBodyComponent {
	vector3df angularMomentum;
	quaternion orientation;
	vector3df position;
	vector3df momentum;

	quaternion spin;
	vector3df angularVelocity;
	vector3df velocity;

	f32 mass = 1;
	f32 inverseMass = 1;
	f32 inertia = 1;
	f32 inverseInertia = 1;

	void applyImpulse(vector3df impulse);
	void applyAngularImpulse(vector3df angularImpulse);

	void recalculate();
};

struct Collider
{
	aabbox3df aaBoundingBox = aabbox3df();
	RigidBodyComponent* body;
};

void integratePhysicsSystem(Scene& scene, f32 dt);
	
void checkCollisions(vector<Collider*> colliders);

#endif
