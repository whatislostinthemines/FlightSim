#pragma once

#ifndef GUIPAUSEMENU_H
#define GUIPAUSEMENU_H
#include "BaseHeader.h"
#include "GuiDialog.h"

class GuiController;
class GameStateController;

enum PAUSE_MENU_BUTTONS
{
	GUI_PAUSE_RESUME,
	GUI_PAUSE_SETTINGS,
	GUI_PAUSE_EXIT_TO_MENU
};

class GuiPauseMenu : public GuiDialog
{
	public:
		GuiPauseMenu(GuiController* controller) : GuiDialog(controller), root(0), resumeGame(0), pauseSettings(0), exitToMenus(0) {}
		~GuiPauseMenu() {}

		virtual void init();
		virtual void show() { root->setVisible(true); isVisible = true; }
		virtual void hide() { root->setVisible(false); isVisible = false; }
		virtual void handleEvent(const SEvent& event);
	private:
		IGUIStaticText* root;
		IGUIButton* resumeGame;
		IGUIButton* pauseSettings;
		IGUIButton* exitToMenus;

};

#endif