#pragma once
#include <irrlicht.h>
#include <vector>
#include "ECS.h"
#include "ColliderComponent.h"


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

void integratePhysicsSystem(Scene& scene, f32 dt);

bool collide(SphereColliderComponent sphere, SphereColliderComponent otherSphere);
bool collide(SphereColliderComponent sphere, AxisAlignedBoundingBoxColliderComponent otherAABB);
bool collide(SphereColliderComponent sphere, OrientedBoundingBoxColliderComponent otherOBB);
bool collide(SphereColliderComponent sphere, CapsuleColliderComponent otherCapsule);

bool collide(AxisAlignedBoundingBoxColliderComponent aABB, SphereColliderComponent otherSphere);
bool collide(AxisAlignedBoundingBoxColliderComponent aABB, AxisAlignedBoundingBoxColliderComponent otherAABB);
bool collide(AxisAlignedBoundingBoxColliderComponent aABB, OrientedBoundingBoxColliderComponent otherOBB);
bool collide(AxisAlignedBoundingBoxColliderComponent aABB, CapsuleColliderComponent otherCapsule);

bool collide(OrientedBoundingBoxColliderComponent oBB, SphereColliderComponent otherSphere);
bool collide(OrientedBoundingBoxColliderComponent oBB, AxisAlignedBoundingBoxColliderComponent otherAABB);
bool collide(OrientedBoundingBoxColliderComponent oBB, OrientedBoundingBoxColliderComponent otherOBB);
bool collide(OrientedBoundingBoxColliderComponent oBB, CapsuleColliderComponent otherCapsule);

bool collide(CapsuleColliderComponent capsule, SphereColliderComponent otherSphere);
bool collide(CapsuleColliderComponent capsule, AxisAlignedBoundingBoxColliderComponent otherAABB);
bool collide(CapsuleColliderComponent capsule, OrientedBoundingBoxColliderComponent otherOBB);
bool collide(CapsuleColliderComponent capsule, CapsuleColliderComponent otherCapsule);

#endif
