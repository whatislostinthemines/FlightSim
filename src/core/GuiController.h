#pragma once

#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H
#include "BaseHeader.h"
#include "GuiDialog.h"
#include "GuiMainMenu.h"

class GameStateController;

class GuiController
{
	public:
		GuiController(GameStateController* controller);
		bool OnEvent(const SEvent& event);
		IrrlichtDevice* device;
		IVideoDriver* driver;
		ISceneManager* smgr;
		IGUIEnvironment* guienv;

		GameStateController* stateController;
		void init();
		void close();
		void update();
		GuiDialog* getActiveDialog() { return activeDialog; }
	private:
		GuiDialog* activeDialog;
		//to-do list: add hookups to store the various menus as well as change the active dialog
};

#endif