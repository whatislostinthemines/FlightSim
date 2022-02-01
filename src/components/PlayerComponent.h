#pragma once

#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "BaseHeader.h"

struct PlayerComponent
{
	ICameraSceneNode* camera;
	ISceneNode* target;
	//values for how much the camera swings around
	f32 slerpFactor = 20.f;
	f32 velocityFactor = .1f;
};

#endif