#pragma once

#ifndef GUIDIALOG_H
#define GUIDIALOG_H
#include "BaseHeader.h"

class GuiController;

class GuiDialog
{
	public:

		GuiDialog(GuiController* controller) { guiController = controller;}
		virtual ~GuiDialog() {}

		//These functions MUST be implemented. How that gets done can vary.
		//Easiest way is to declare a gui element as "root" in your inherited class,
		//then setting up all your other elements as childen of that node.
		//For an example, go check GuiMainMenu.h
		virtual void init() = 0;
		virtual void show() = 0;
		virtual void hide() = 0;

		//The GUI controller passes events to the currently active dialog and lets them handle it.
		//Such as button clicking! Or mouse movement, if you want to do something odd.
		virtual void handleEvent(const SEvent& event) = 0;
		bool isDialogVisible() { return isVisible; }
	protected:
		bool isVisible = false;
		GuiController* guiController;
};

#endif

