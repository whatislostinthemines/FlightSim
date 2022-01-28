#include "GuiController.h"

GuiController::GuiController(IrrlichtDevice* dev)
{
	device = dev;
	driver = dev->getVideoDriver();
	smgr = dev->getSceneManager();
	guienv = dev->getGUIEnvironment();
}

void GuiController::init()
{
	//default main menu
}

void GuiController::close()
{
	//delete it all!
}

bool GuiController::OnEvent(const SEvent& event)
{
	switch (event.EventType) {
		case EET_MOUSE_INPUT_EVENT:
			break;
		case EET_KEY_INPUT_EVENT:
			break;
		case EET_GUI_EVENT:
			if (activeDialog) {
				activeDialog->handleEvent(event);
			}
			break;
	}
	return false;
}

void GuiController::update()
{
	//...I'm not actually sure anything needs to be done, but if it does, it gets done here.
}