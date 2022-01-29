#include "GuiMainMenu.h"
#include "GuiController.h"
#include "GameStateController.h"
#include <iostream>

GuiMainMenu::~GuiMainMenu()
{
	delete startGame;
	delete settings;
	delete quitGame;
	delete root;
}

void GuiMainMenu::init()
{
	dimension2du size = guiController->driver->getScreenSize();
	u32 verticalSlice = size.Height / 6;
	u32 horizontalPos = size.Width / 3;
	dimension2du buttonSize(horizontalPos, verticalSlice); //third of the screen size and a sixth of the height
	root = guiController->guienv->addStaticText(L"MAIN MENU", rect<s32>(position2di(0,0), size));
	startGame = guiController->guienv->addButton(rect<s32>(position2di(horizontalPos, 32), buttonSize), root, GUI_START_GAME, L"Start Game", L"Are you prepared to shoot rocks?");
	settings = guiController->guienv->addButton(rect<s32>(position2di(horizontalPos, 32 * 2 + verticalSlice), buttonSize), root, GUI_SETTINGS, L"Settings", L"Like we have any worthwhile settings.");
	quitGame = guiController->guienv->addButton(rect<s32>(position2di(horizontalPos, 32 * 3 + (verticalSlice * 2)), buttonSize), root, GUI_QUIT_GAME, L"Quit game", L"You'll be back.");
	root->setVisible(false);
}

void GuiMainMenu::show()
{
	root->setVisible(true);
}

void GuiMainMenu::hide()
{
	root->setVisible(false);
}

void GuiMainMenu::close()
{
	delete startGame;
	delete settings;
	delete quitGame;
	delete root;
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
			IGUIEnvironment* env = guiController->guienv;
			if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED) {
				switch (id) {
				case GUI_START_GAME:
					if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED) {
						guiController->stateController->setState(GAME_RUNNING);
					}
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