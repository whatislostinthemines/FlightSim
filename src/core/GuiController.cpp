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
	activeDialog = new GuiMainMenu(this);
	activeDialog->init();
	activeDialog->show();
	//default main menu
}

void GuiController::close()
{
	if (activeDialog) {
		activeDialog = nullptr;
	}
	guienv->clear();
	//delete it all!
	//might want to call gui clear actually
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