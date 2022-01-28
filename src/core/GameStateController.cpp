#include "GameStateController.h"
#include <iostream>

GameStateController::GameStateController(IrrlichtDevice* dev)
{
	device = dev;
	driver = 0;
	smgr = 0;
	guienv = 0;
	then = 0;
	gameController = 0;
	init();
}

void GameStateController::init()
{
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	device->setEventReceiver(this);
	guienv->setUserEventReceiver(this);
	then = device->getTimer()->getTime();
	state = GAME_RUNNING;

	gameController = new GameController(device);
	gameController->init();
	gameController->initDefaultScene();
}

bool GameStateController::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_KEY_INPUT_EVENT) {
		if (event.KeyInput.Key == KEY_ESCAPE && event.KeyInput.PressedDown) {
			if (state == GAME_RUNNING) {
				state = GAME_PAUSED;
				// pause it
			}
			else if (state == GAME_PAUSED) {
				state = GAME_RUNNING;
				//unpause it
			}
		}
	}
	switch (state) {
		case GAME_MENUS:
			guiController->OnEvent(event);
			break;
		case GAME_RUNNING:
			gameController->OnEvent(event);
			break;
		case GAME_PAUSED:
			break;
	}
	return false;
}

void GameStateController::mainLoop()
{
	u32 lastFPS = -1;
	while (device->run()) {
		u32 now = device->getTimer()->getTime();
		switch (state) {
			case GAME_MENUS:
				guiController->update();
				break;
			case GAME_RUNNING:
				gameController->update();
				break;
			case GAME_PAUSED:
				break;
		}
		then = now;

		driver->beginScene(true, true, SColor(255, 20, 20, 20));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();

		int fps = driver->getFPS();
		stringw tmp(L"Flight [");
		tmp += driver->getName();
		tmp += L"] FPS: ";
		if (lastFPS != fps) {
			tmp += fps;
		}
		else tmp += lastFPS;

		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}
}