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

		virtual void init() = 0;
		virtual void show() = 0;
		virtual void hide() = 0;

		virtual void handleEvent(const SEvent& event) = 0;
		bool isDialogVisible() { return isVisible; }
	protected:
		bool isVisible = false;
		GuiController* guiController;
};

#endif

