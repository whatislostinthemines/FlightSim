#pragma once

#ifndef SHIPCOMPONENT_H
#define SHIPCOMPONENT_H
#include "BaseHeader.h"
#include "ECS.h"
#include <vector>

const int MAX_HARDPOINTS = 8;

struct ShipComponent {
	unsigned int hardpointCount;
	vector3df hardpoints[MAX_HARDPOINTS];
	EntityId weapons[MAX_HARDPOINTS];
	f32 speed;
	f32 rotSpeed;
};

#endif