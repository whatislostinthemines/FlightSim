#pragma once
#ifndef DEFAULTAIUPDATESYSTEM_H
#define DEFAULTAIUPDATESYSTEM_H
#include "BaseHeader.h"
#include "ECS.h"
#include "AIComponent.h"

class SceneManager;

void defaultAIUpdateSystem(SceneManager* manager, EntityId id);

#endif 