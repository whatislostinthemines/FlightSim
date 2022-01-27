#pragma once
#ifndef WEAPONFIRINGSYSTEM_H
#define WEAPONFIRINGSYSTEM_H
#include "BaseHeader.h"
#include "ECS.h"
#include "ProjectileSystem.h"
#include "WeaponInfoComponent.h"
#include "ShipComponent.h"
#include "GameFunctions.h"

class GameController;
class SceneManager;

void weaponFiringSystem(SceneManager* manager, f32 dt);

#endif
