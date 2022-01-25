#pragma once

#ifndef COLLISIONCHECKINGSYSTEM_H
#define COLLISIONCHECKINGSYSTEM_H
#include "BaseHeader.h"
#include "WeaponInfoComponent.h"
#include "IrrlichtComponent.h"
#include "BulletRigidBodyComponent.h"
#include "ProjectileSystem.h"

void collisionCheckingSystem(btDiscreteDynamicsWorld* world, Scene& scene);

#endif