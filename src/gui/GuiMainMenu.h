#pragma once

#ifndef GUIMAINMENU_H
#define GUIMAINMENU_H

#include "BaseHeader.h"
#include "GuiDialog.h"

class GameStateController;
class GuiController;

enum MAIN_MENU_BUTTONS
{
	GUI_START_GAME,
	GUI_SETTINGS,
	GUI_QUIT_GAME
};

class GuiMainMenu : public GuiDialog
{
	public:
		GuiMainMenu(GuiController* controller) : GuiDialog(controller), startGame(0), settings(0), quitGame(0) {}
		~GuiMainMenu();

		virtual void init();
		virtual void show();
		virtual void hide();
		virtual void close();
		virtual void handleEvent(const SEvent& event);
	private:
		IGUIStaticText* root;
		IGUIButton* startGame;
		IGUIButton* settings;
		IGUIButton* quitGame;
};


#endif
