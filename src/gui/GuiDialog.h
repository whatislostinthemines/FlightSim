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

		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void clear() = 0;

		virtual void handleEvent(const SEvent& event) = 0;
	protected:
		bool isVisible = false;
		GuiController* guiController;
};

#endif

