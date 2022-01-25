#pragma once
#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H
#include "BaseHeader.h"
#include "ECS.h"
#include "IrrlichtComponent.h"
#include "BulletRigidBodyComponent.h"
#include "HealthComponent.h"

void destroyHealthObject(btDiscreteDynamicsWorld* world, Scene& scene, EntityId id);
void updateHealthSystem(btDiscreteDynamicsWorld* world, Scene& scene);

#endif 

