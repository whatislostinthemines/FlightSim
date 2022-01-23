#pragma once
#ifndef BULLETRIGIDBODYCOMPONENT_H
#define BULLETRIGIDBODYCOMPONENT_H
#include "BaseHeader.h"
#include "ECS.h"
#include "IrrlichtComponent.h"

void initializeRigidBodyFromIrrlicht(btDiscreteDynamicsWorld* world, Scene& scene, EntityId id);
vector3df bulletVectorToIrrlicht(btVector3 vec);
btVector3 irrlichtVectorToBullet(vector3df vec);

struct BulletRigidBodyComponent
{
	btTransform transform;
	btCollisionShape* shape;
	btRigidBody* rigidBody;
	btDefaultMotionState* motionState;
};

#endif
