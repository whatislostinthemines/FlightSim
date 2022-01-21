#pragma once

#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include <irrlicht.h>

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

struct PlayerComponent
{
	ICameraSceneNode* camera;
};

#endif