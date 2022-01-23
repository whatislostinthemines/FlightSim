#pragma once

#ifndef WEAPONINFOCOMPONENT_H
#define WEAPONINFOCOMPONENT_H
#include "BaseHeader.h"
#include "ECS.h"

enum WEAPON_TYPE {
	WEP_LASER,
	WEP_MISSILE,
	WEP_GRAPPLE
};

//WEAPON ENTITIES:
//Irrlicht component, weapon info component

struct WeaponInfoComponent
{
	WEAPON_TYPE type;
	unsigned int firingSpeed;
	unsigned int range;
	bool isFiring;
};

//PROJECTILE ENTITIES:
//Irrlicht component, projectile info component, rigid body component

struct ProjectileInfoComponent
{
	WEAPON_TYPE type;
	unsigned int speed;
};
#endif