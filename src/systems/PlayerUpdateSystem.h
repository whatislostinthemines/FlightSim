#pragma once

#ifndef HEADER_H
#define HEADER_H
#include "BaseHeader.h"

#include "ECS.h"
#include "IrrlichtComponent.h"
#include "PlayerComponent.h"
#include "BulletRigidBodyComponent.h"
#include "IrrlichtUtils.h"

class SceneManager;
class GameController;

void playerUpdateSystem(SceneManager* manager, Scene& scene, f32 dt);

#endif
