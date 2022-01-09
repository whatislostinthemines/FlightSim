#include "PlayerShip.h"
#include "FlightEventReceiver.h"

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
	posUpdate(time);
	vector3df offset = vector3df(0, 10, 20);
	camera->setTarget(node->getPosition());
}