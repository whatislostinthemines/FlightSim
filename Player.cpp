#include "Player.h"
#include "Controller.h"
#include <iostream>

Player::Player(Ship* pship, ICameraSceneNode* ncamera, Controller* cont) 
{
	camRig.camera = ncamera;
	controller = cont;
	ship = pship;
}

Player::Player()
{
	camRig.camera = 0;
}
void Player::update(f32 time)
{
	//WASD movement, space+ctrl up/down
	//QE yaw RF pitch ZC roll
	//X stop
	if (controller->isKeyDown(KEY_KEY_S)) {
		ship->accelerateBackward();
	}
	if (controller->isKeyDown(KEY_KEY_W)) {
		ship->accelerateForward();
	}
	if (controller->isKeyDown(KEY_KEY_A)) {
		ship->strafeLeft();
	}
	if (controller->isKeyDown(KEY_KEY_D)) {
		ship->strafeRight();
	}
	if (controller->isKeyDown(KEY_SPACE)) {
		ship->strafeUp();
	}
	if (controller->isKeyDown(KEY_LCONTROL)) {
		ship->strafeDown();
	}
	if (controller->isKeyDown(KEY_KEY_E)) {
		ship->yawRight();
	}
	if (controller->isKeyDown(KEY_KEY_Q)) {
		ship->yawLeft();
	}
	if (controller->isKeyDown(KEY_KEY_R)) {
		ship->pitchUp();
	}
	if (controller->isKeyDown(KEY_KEY_F)) {
		ship->pitchDown();
	}
	if (controller->isKeyDown(KEY_KEY_Z)) {
		ship->rollLeft();
	}
	if (controller->isKeyDown(KEY_KEY_C)) {
		ship->rollRight();
	}
	if (controller->isKeyDown(KEY_KEY_X)) {
		ship->stopMoving();
	}
	if(controller->isMouseEnabled()) {
		//hookup for what the mouse is doing
		MouseStateMap mouseState = controller->getMouseState();
		dimension2du screenSize = controller->driver->getScreenSize();
		vector2di pos = mouseState.Position;
		vector2di center(screenSize.Width / 2, screenSize.Height / 2);

		/*
		if (((f32)pos.X > (f32)center.X * 1.2f) || (f32)pos.X < (f32)center.X * 0.8f) {
			torque.Y += maxRotSpeed * ((f32)(pos.X - center.X) * sensitivity);
		}
		if (((f32)pos.Y > (f32)center.Y * 1.2f) || (f32)pos.Y < (f32)center.Y * .8f) {
			torque.X += maxRotSpeed * ((f32)(center.Y - pos.Y) * sensitivity);
		}
		*/

		//ray leading out of the mouse cursor
		line3df ray = controller->smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(mouseState.Position, camRig.camera);
		vector3df turnPoint = ray.getMiddle();
		ship->turnToPos(turnPoint);
		//probably gonna want this later
	}

	ship->posUpdate(time);

	//camera work
	Directions dir;
	dir.up = ship->getUp();
	dir.forward = ship->getForward();
	dir.left = ship->getLeft();

	camRig.moveCamera(&ship->rigidBodyComponent, ship->node, dir, time);

}