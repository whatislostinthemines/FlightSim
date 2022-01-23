#pragma once

#ifndef IRRLICHTRIGIDBODYPOSITIONSYSTEM_H
#define IRRLICHTRIGIDBODYPOSITIONSYSTEM_H
#include "BaseHeader.h"

#include "ECS.h"
#include "IrrlichtComponent.h"
#include "BulletRigidBodyComponent.h"

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

void QuaternionToEuler(const btQuaternion& TQuat, btVector3& TEuler);
void irrlichtRigidBodyPositionSystem(Scene& scene, f32 dt);

#endif
