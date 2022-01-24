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
	f32 firingSpeed; //how long it should take in seconds between shots
	f32 projectileSpeed; //how fast the projectile goes
	f32 range; //how far the projectile goes
	f32 timeSinceLastShot;
	bool isFiring;
};

//PROJECTILE ENTITIES:
//Irrlicht component, projectile info component, rigid body component

struct ProjectileInfoComponent
{
	WEAPON_TYPE type;
	f32 speed;
	f32 range;
	vector3df startPos;
};
#endif