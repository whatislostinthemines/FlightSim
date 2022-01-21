#pragma once

#ifndef FLIGHTEVENTRECEIVER_H
#define FLIGHTEVENTRECEIVER_H
#include <irrlicht.h>
#include "Player.h"
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

		Player player;
		IrrlichtDevice* device;
		IVideoDriver* driver;
		ISceneManager* smgr;
		IGUIEnvironment* guienv;


		Controller(IrrlichtDevice* dev);
		void init(IrrlichtDevice* dev);
		void mainLoop();
		void makePlayer();
		vector<RigidPhysicsObject> makeAsteroids(int numAsteroids);

		bool isMouseEnabled() { return mouseControl; }
		void setMouseEnabled(bool state) {mouseControl = state;}
		bool isKeyDown(EKEY_CODE key);
		MouseStateMap getMouseState() { return MouseState; }
	private:

		Scene scene; 
		bool mouseControl = false;
		u32 then;
		bool keysDown[KEY_KEY_CODES_COUNT];
		MouseStateMap MouseState;
		u32 lastFPS;
};


#endif