#include "PlayerShip.h"
#include "FlightEventReceiver.h"
#include <iostream>

PlayerShip::PlayerShip(IAnimatedMesh* nship, IAnimatedMeshSceneNode* nnode, ICameraSceneNode* ncamera, Controller* cont, f32 mass, f32 inertia) 
	: Ship(nship, nnode, cont, mass, inertia)
{
	camera = ncamera;
}

PlayerShip::PlayerShip() : Ship()
{
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
	if(controller->isMouseEnabled()) {
		//hookup for what the mouse is doing
		MouseStateMap mouseState = controller->getMouseState();
		dimension2du screenSize = controller->driver->getScreenSize();
		vector2di pos = mouseState.Position;
		vector2di center(screenSize.Width / 2, screenSize.Height / 2);

		if (((f32)pos.X > (f32)center.X * 1.2f) || (f32)pos.X < (f32)center.X * 0.8f) {
			torque.Y += maxRotSpeed * ((f32)(pos.X - center.X) * sensitivity);
		}
		if (((f32)pos.Y > (f32)center.Y * 1.2f) || (f32)pos.Y < (f32)center.Y * .8f) {
			torque.X += maxRotSpeed * ((f32)(center.Y - pos.Y) * sensitivity);
		}

		//ray leading out of the mouse cursor
		line3df ray = controller->smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(mouseState.Position, camera);
		//probably gonna want this later
	}

	posUpdate(time);
	camera->setUpVector(getUp());
	vector3df target = node->getPosition() + (rigidBodyComponent.velocity * .1f);
	camera->setTarget(target);

}