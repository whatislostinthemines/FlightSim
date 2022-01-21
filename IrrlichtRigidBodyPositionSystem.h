#pragma once

#ifndef IRRLICHTRIGIDBODYPOSITIONSYSTEM_H
#define IRRLICHTRIGIDBODYPOSITIONSYSTEM_H

#include <irrlicht.h>
#include "ECS.h"
#include "Physics.h"
#include "IrrlichtComponent.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

void irrlichtRigidBodyPositionSystem(Scene& scene, f32 dt);

#endif
