#include "PlayerShip.h"
#include "FlightEventReceiver.h"
#include <iostream>

PlayerShip::PlayerShip(IAnimatedMesh* nship, IAnimatedMeshSceneNode* nnode, ICameraSceneNode* ncamera, Controller* cont)
{
	controller = cont;
	ship = nship;
	node = nnode;
	camera = ncamera;
}

PlayerShip::PlayerShip()
{
	controller = 0;
	ship = 0;
	node = 0;
	camera = 0;
}
void PlayerShip::update(f32 time)
{
	//WASD movement, space+ctrl up/down
	//QE yaw RF pitch ZC roll
	//X stop

	if (controller->isKeyDown(KEY_KEY_S)) {
		accelerateBackward();
	}
	if (controller->isKeyDown(KEY_KEY_W)) {
		accelerateForward();
	}
	if (controller->isKeyDown(KEY_KEY_A)) {
		strafeLeft();
	}
	if (controller->isKeyDown(KEY_KEY_D)) {
		strafeRight();
	}
	if (controller->isKeyDown(KEY_SPACE)) {
		strafeUp();
	}
	if (controller->isKeyDown(KEY_LCONTROL)) {
		strafeDown();
	}
	if (controller->isKeyDown(KEY_KEY_E)) {
		yawRight();
	}
	if (controller->isKeyDown(KEY_KEY_Q)) {
		yawLeft();
	}
	if (controller->isKeyDown(KEY_KEY_R)) {
		pitchUp();
	}
	if (controller->isKeyDown(KEY_KEY_F)) {
		pitchDown();
	}
	if (controller->isKeyDown(KEY_KEY_Z)) {
		rollLeft();
	}
	if (controller->isKeyDown(KEY_KEY_C)) {
		rollRight();
	}
	if (controller->isKeyDown(KEY_KEY_X)) {
		stopMoving();
	}

	//hookup for what the mouse is doing
	MouseStateMap mouseState = controller->getMouseState();

	posUpdate(time);
	camera->setUpVector(getUp());
	vector3df target = node->getPosition() + (velocity * .1f);
	camera->setTarget(target);

}