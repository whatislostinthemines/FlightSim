#pragma once

#ifndef SHIPMOVEMENTSYSTEM_H
#define SHIPMOVEMENTSYSTEM_H
#include "BaseHeader.h"

#include "ECS.h"
#include "Physics.h"
#include "InputComponent.h"
#include "IrrlichtComponent.h"

void shipMovementSystem(Scene& scene, f32 dt);

#endif