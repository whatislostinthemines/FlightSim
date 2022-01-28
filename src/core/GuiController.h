#pragma once

#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H
#include "BaseHeader.h"
#include "GuiDialog.h"

class GuiController
{
	public:
		GuiController(IrrlichtDevice* dev);
		bool OnEvent(const SEvent& event);
		IrrlichtDevice* device;
		IVideoDriver* driver;
		ISceneManager* smgr;
		IGUIEnvironment* guienv;
		void init();
		void close();
		void update();
	private:
		GuiDialog* activeDialog;
};

#endif