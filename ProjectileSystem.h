#pragma once

#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include "BaseHeader.h"
#include "ECS.h"
#include "WeaponInfoComponent.h"
#include "IrrlichtComponent.h"
#include "BulletRigidBodyComponent.h"

class Controller;

void createProjectileEntity(btDiscreteDynamicsWorld* world, Scene& scene, Controller* controller, vector3df spawnPos, vector3df direction);

#endif