#pragma once

#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include "BaseHeader.h"
#include "ECS.h"
#include "WeaponInfoComponent.h"
#include "IrrlichtComponent.h"
#include "BulletRigidBodyComponent.h"
#include "GameFunctions.h"

class GameController;
class SceneManager;

void projectileRangeSystem(SceneManager* manager);

#endif