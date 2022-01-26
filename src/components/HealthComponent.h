#pragma once

#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H
#include "BaseHeader.h"
#include "ECS.h"

struct HealthComponent
{
	f32 health;
	f32 maxHealth;
};

#endif