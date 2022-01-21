#pragma once

#ifndef HEADER_H
#define HEADER_H
#include <irrlicht.h>
#include "ECS.h"
#include "IrrlichtComponent.h"
#include "PlayerComponent.h"
#include "Physics.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

void playerUpdateSystem(Scene& scene, f32 dt);

#endif
