#pragma once

#ifndef FLIGHTEVENTRECEIVER_H
#define FLIGHTEVENTRECEIVER_H
#include "BaseHeader.h"

#include "ECS.h"
#include "SceneManager.h"
#include "IrrlichtComponent.h"
#include "InputComponent.h"
#include "GameFunctions.h"

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
		btDiscreteDynamicsWorld* bWorld;

		Controller(IrrlichtDevice* dev);
		void init(IrrlichtDevice* dev);
		void mainLoop();

	private:

		SceneManager sceneECS; 
		u32 then;
		u32 lastFPS;
};


#endif