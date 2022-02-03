#pragma once
#ifndef AIUPDATESYSTEM_H
#define AIUPDATESYSTEM_H
#include "BaseHeader.h"
#include "ECS.h"
#include "AIComponent.h"
#include "DefaultAIUpdateSystem.h"

class SceneManager;

void AIUpdateSystem(SceneManager* manager, f32 dt);

#endif 