#pragma once

#ifndef FLIGHTEVENTRECEIVER_H
#define FLIGHTEVENTRECEIVER_H
#include <irrlicht.h>
#include "PlayerShip.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

enum PLAYER_MOVEMENT {
	PLAYER_MOVE_FORWARD,
	PLAYER_MOVE_BACKWARD,
	PLAYER_STRAFE_LEFT,
	PLAYER_STRAFE_RIGHT,
	PLAYER_MOVE_UP,
	PLAYER_MOVE_DOWN
};

struct KeyMap
{
	KeyMap() {}
	KeyMap(PLAYER_MOVEMENT action, EKEY_CODE KeyCode) : move(action), keyCode(KeyCode) {}
	PLAYER_MOVEMENT move;
	EKEY_CODE keyCode;
};

struct MouseStateMap
{
	position2di Position;
	bool leftDown;
	bool rightDown;
	MouseStateMap() : leftDown(false), rightDown(false) {}
};

class Controller : public IEventReceiver
{
	public:
		virtual bool OnEvent(const SEvent& event);

		PlayerShip player;
		IrrlichtDevice* device;
		IVideoDriver* driver;
		ISceneManager* smgr;
		IGUIEnvironment* guienv;


		Controller(IrrlichtDevice* dev);
		void init(IrrlichtDevice* dev);
		void mainLoop();
		void makePlayer();
		void makeAsteroids(int numAsteroids);

		bool isKeyDown(EKEY_CODE key);
		MouseStateMap getMouseState() { return MouseState; }
	private:
		u32 then;
		bool keysDown[KEY_KEY_CODES_COUNT];
		MouseStateMap MouseState;
		u32 lastFPS;
};


#endif