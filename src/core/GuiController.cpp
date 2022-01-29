#include "GuiController.h"
#include "GameStateController.h"

GuiController::GuiController(GameStateController* controller)
{
	stateController = controller;
	device = controller->device;
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	activeDialog = 0;
}

void GuiController::init()
{
	menus.menuDialogs[GUI_MAIN_MENU] = new GuiMainMenu(this);
	menus.menuDialogs[GUI_MAIN_MENU]->init();
	menus.menuDialogs[GUI_PAUSE_MENU] = new GuiPauseMenu(this);
	menus.menuDialogs[GUI_PAUSE_MENU]->init();

	activeDialog = menus.menuDialogs[GUI_MAIN_MENU];
	activeDialog->show();
	//default main menu
}

void GuiController::close()
{
	if (activeDialog) {
		activeDialog->hide();
		activeDialog = nullptr;
	}
}

bool GuiController::OnEvent(const SEvent& event)
{
	if (activeDialog) {
		activeDialog->handleEvent(event);
	}
	return false;
}

void GuiController::update()
{
	//...I'm not actually sure anything needs to be done, but if it does, it gets done here.
}

void GuiController::setActiveDialog(MENU_TYPE menu)
{
	if (activeDialog) {
		activeDialog->hide();
	}
	activeDialog = menus.menuDialogs[menu];
	activeDialog->show();
}