#pragma once

#ifndef FLIGHTEVENTRECEIVER_H
#define FLIGHTEVENTRECEIVER_H
#include <irrlicht.h>
#include "ECS.h"
#include "SceneManager.h"
#include "IrrlichtComponent.h"
#include "InputComponent.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;


struct MouseStateMap
{
	vector2di Position;
	bool leftDown;
	bool rightDown;
	MouseStateMap() : leftDown(false), rightDown(false) {}
};

class Controller : public IEventReceiver
{
	public:
		virtual bool OnEvent(const SEvent& event);

		IrrlichtDevice* device;
		IVideoDriver* driver;
		ISceneManager* smgr;
		IGUIEnvironment* guienv;


		Controller(IrrlichtDevice* dev);
		void init(IrrlichtDevice* dev);
		void mainLoop();
		void makePlayer();
		void makeAsteroids();

	private:

		SceneManager sceneECS; 
		u32 then;
		u32 lastFPS;
};


#endif