#pragma once
#ifndef BULLETRIGIDBODYCOMPONENT_H
#define BULLETRIGIDBODYCOMPONENT_H
#include "BaseHeader.h"
#include "ECS.h"
#include "IrrlichtComponent.h"
#include "GameFunctions.h"

struct BulletRigidBodyComponent
{
	btRigidBody rigidBody = btRigidBody(0,0,0,btVector3(0,0,0));
};

#endif
