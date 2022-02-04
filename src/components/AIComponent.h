#pragma once

#ifndef AICOMPONENT_H
#define AICOMPONENT_H
#include "BaseHeader.h"
#include "ECS.h"

const enum AI_STATE
{
	AI_STATE_IDLE,
	AI_STATE_PURSUIT,
	AI_STATE_FLEE,
	AI_STATE_SEARCH,
	AI_STATE_GET_HELP,
	AI_STATE_PATROL
};

const enum AI_TYPE //different ships would have different AI patterns
{
	AI_TYPE_DEFAULT
};

struct AIComponent
{
	AI_TYPE AIType;
	AI_STATE state;
	f32 detectionRadius;
	array<EntityId> contacts;
	bool nearbyHostiles;
};

#endif