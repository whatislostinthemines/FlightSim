#pragma once
#ifndef WEAPONFIRINGSYSTEM_H
#define WEAPONFIRINGSYSTEM_H
#include "BaseHeader.h"
#include "ECS.h"
#include "ProjectileSystem.h"
#include "WeaponInfoComponent.h"
#include "ShipComponent.h"

class Controller;

void weaponFiringSystem(Scene& scene, btDiscreteDynamicsWorld* world, Controller* controller);

#endif
