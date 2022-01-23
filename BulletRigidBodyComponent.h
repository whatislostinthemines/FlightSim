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
	btRigidBody rigidBody = btRigidBody(0,0,0,btVector3(0,0,0));
};

#endif
