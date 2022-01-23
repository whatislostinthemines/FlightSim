#pragma once

#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "BaseHeader.h"

enum PLAYER_MOVEMENT {
	PLAYER_MOVE_FORWARD,
	PLAYER_MOVE_BACKWARD,
	PLAYER_STRAFE_LEFT,
	PLAYER_STRAFE_RIGHT,
	PLAYER_MOVE_UP,
	PLAYER_MOVE_DOWN
};

struct InputComponent {
	bool keysDown[KEY_KEY_CODES_COUNT];
	bool mouseControlEnabled = false;
	vector2df mousePosition;
	bool leftMouseDown;
	bool rightMouseDown;
	bool isKeyDown(EKEY_CODE key) { return keysDown[key]; }
};

#endif