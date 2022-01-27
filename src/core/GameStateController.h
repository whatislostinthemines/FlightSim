#pragma once

#ifndef GAMESTATECONTROLLER_H
#define GAMESTATECONTROLLER_H
#include "BaseHeader.h"
#include "GameController.h"

enum GAME_STATE
{
	GAME_MENUS = 0,
	GAME_RUNNING = 1,
	GAME_PAUSED = 2
};

class GameStateController : public IEventReceiver
{
	public:
		virtual bool OnEvent(const SEvent& event);

		IrrlichtDevice* device;
		IVideoDriver* driver;
		ISceneManager* smgr;
		IGUIEnvironment* guienv;

		GameStateController(IrrlichtDevice* dev);
		void init();
		void mainLoop();
	private:
		u32 then;
		GAME_STATE state;
		GameController* gameController;



};

#endif