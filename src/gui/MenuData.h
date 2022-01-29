#pragma once

#ifndef MENUDATA_H
#define MENUDATA_H
#include <map>

#include "BaseHeader.h"
#include "GuiDialog.h"
#include "GuiMainMenu.h"
#include "GuiPauseMenu.h"

enum MENU_TYPE {
	GUI_MAIN_MENU,
	GUI_PAUSE_MENU
};

struct MenuData
{
	std::map<MENU_TYPE, GuiDialog*> menuDialogs;
};

#endif