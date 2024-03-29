#include "GuiMainMenu.h"
#include "GuiController.h"
#include "GameStateController.h"
#include <iostream>

void GuiMainMenu::init()
{
	//Convenience declarations here to determine how big a button should be.
	//In this case, it's setting up some fairly large buttons straight down the middle of the screen.
	dimension2du size = guiController->driver->getScreenSize();
	u32 verticalSlice = size.Height / 6;
	u32 horizontalPos = size.Width / 3;
	dimension2du buttonSize(horizontalPos, verticalSlice); //third of the screen size and a sixth of the height
	root = guiController->guienv->addStaticText(L"MAIN MENU", rect<s32>(position2di(0,0), size));
	//All buttons have the root node set as the parent. This allows a single call to root->setVisible in order to display or hide the menu.
	startGame = guiController->guienv->addButton(rect<s32>(position2di(horizontalPos, 32), buttonSize), root, GUI_START_GAME, L"Start Game", L"Are you prepared to shoot rocks?");
	settings = guiController->guienv->addButton(rect<s32>(position2di(horizontalPos, 32 * 2 + verticalSlice), buttonSize), root, GUI_SETTINGS, L"Settings", L"Like we have any worthwhile settings.");
	quitGame = guiController->guienv->addButton(rect<s32>(position2di(horizontalPos, 32 * 3 + (verticalSlice * 2)), buttonSize), root, GUI_QUIT_GAME, L"Quit Game", L"You'll be back.");
	root->setVisible(false);
}

void GuiMainMenu::handleEvent(const SEvent& event)
{
	switch (event.EventType)
	{
		case EET_MOUSE_INPUT_EVENT:
			break;
		case EET_KEY_INPUT_EVENT:
			break;
		case EET_GUI_EVENT:
			s32 id = event.GUIEvent.Caller->getID();
			if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED) { //important: don't forget this if statement on buttons, otherwise all of 'em will try and activate at once.
				switch (id) {
				case GUI_START_GAME:
					guiController->stateController->setState(GAME_RUNNING);
					break;
				case GUI_SETTINGS:
					break;
				case GUI_QUIT_GAME:
					guiController->device->closeDevice();
					break;
				}
			}
			break;
	}
}