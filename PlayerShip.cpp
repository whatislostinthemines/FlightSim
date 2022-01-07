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

	vector3df pos = node->getPosition();
	vector3df rot = node->getRotation();

	if (controller->isKeyDown(KEY_KEY_S)) {
		pos.Z += time * speed;
	}
	if (controller->isKeyDown(KEY_KEY_W)) {
		pos.Z -= time * speed;
	}
	if (controller->isKeyDown(KEY_KEY_A)) {
		pos.X += time * speed;
	}
	if (controller->isKeyDown(KEY_KEY_D)) {
		pos.X -= time * speed;
	}
	if (controller->isKeyDown(KEY_SPACE)) {
		pos.Y += time * speed;
	}
	if (controller->isKeyDown(KEY_LCONTROL)) {
		pos.Y -= time * speed;
	}
	if (controller->isKeyDown(KEY_KEY_E)) {
		rot.Y += time * rotspeed;
	}
	if (controller->isKeyDown(KEY_KEY_Q)) {
		rot.Y -= time * rotspeed;
	}
	node->setPosition(pos);
	node->setRotation(rot);
	camera->setTarget(pos);
}