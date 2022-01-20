#pragma once
#include <irrlicht.h>
#include <vector>


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

	void recalculate();
};

struct Collider
{
	aabbox3df aaBoundingBox = aabbox3df();
	RigidBodyComponent* body;
};

class Physics {

public:
	static void integrate(vector<RigidBodyComponent*> rigidBodies, f32 dt);
	static void applyImpulse(RigidBodyComponent* rigidBody, vector3df impulse);
	static void applyAngularImpulse(RigidBodyComponent* rigidBody, vector3df angularImpulse);
	static void checkCollisions(vector<Collider*> colliders);
};

#endif
