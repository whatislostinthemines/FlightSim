#include "FlightEventReceiver.h"
#include <iostream>
#include <random>

Controller::Controller(IrrlichtDevice* dev)
{
	player = PlayerShip(0, 0, 0, 0);
	device = 0;
	smgr = 0;
	guienv = 0;
	driver = 0;
	lastFPS = -1;
	then = 0;
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i) {
		keysDown[i] = false;
	}
	init(dev);
}

vector3df randomVector()
{
	f32 x = static_cast<f32>(rand() / static_cast <f32>(900));
	f32 y = static_cast<f32>(rand() / static_cast <f32>(900));
	f32 z = static_cast<f32>(rand() / static_cast <f32>(900));

	return vector3df(x,y,z);
}

vector3df randomRotationVector()
{
	f32 x = static_cast<f32>(rand() / static_cast <f32>(180));
	f32 y = static_cast<f32>(rand() / static_cast <f32>(180));
	f32 z = static_cast<f32>(rand() / static_cast <f32>(180));

	return vector3df(x, y, z);
}

bool Controller::isKeyDown(EKEY_CODE key)
{
	if (keysDown[key]) return true;
	return false;
}

void Controller::init(IrrlichtDevice* dev)
{
	device = dev;
	driver = device->getVideoDriver();
	SColorf col(1, 1, 1);
	driver->setAmbientLight(col);
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	device->setEventReceiver(this);
	guienv->setUserEventReceiver(this);
	then = device->getTimer()->getTime();
}

bool Controller::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_KEY_INPUT_EVENT) {
		keysDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		return true;
	}
	if (event.EventType == EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
			case EMIE_LMOUSE_PRESSED_DOWN: {
				MouseState.leftDown = true;
				break;
			}
			case EMIE_LMOUSE_LEFT_UP: {
				MouseState.leftDown = false;
				break;
			}
			case EMIE_RMOUSE_PRESSED_DOWN: {
				MouseState.rightDown = true;
				break;
			}
			case EMIE_RMOUSE_LEFT_UP: {
				MouseState.rightDown = false;
				break;
			}
			case EMIE_MOUSE_MOVED: {
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;
			}
			default: { //can add wheel or double clicks or whatever
				break;
			}
		}
	}
	return false;
}

void Controller::makePlayer()
{
	IAnimatedMesh* playerMesh = smgr->getMesh("models/hellkitten/hellkitten.obj");
	IAnimatedMeshSceneNode* playerNode = smgr->addAnimatedMeshSceneNode(playerMesh);
	//playerNode->setMaterialFlag(EMF_LIGHTING, false);
	ICameraSceneNode* camera = smgr->addCameraSceneNode(playerNode, vector3df(0, 10, 20), playerNode->getPosition(), PLAYER_CAMERA, true);
	//camera->bindTargetAndRotation(true);
	player = PlayerShip(playerMesh, playerNode, camera, this);

}

void Controller::makeAsteroids(int numAsteroids)
{
	IAnimatedMesh* asteroidMesh = smgr->getMesh("models/asteroid/Asteroid.obj");
	for (int i = 0; i < numAsteroids; ++i) {
		IAnimatedMeshSceneNode* roid = smgr->addAnimatedMeshSceneNode(asteroidMesh, 0, -1, randomVector(), randomRotationVector());
	}
}

void Controller::mainLoop()
{
	makePlayer();

	makeAsteroids(40);
	ISceneNode* n = smgr->addLightSceneNode(0, vector3df(0, 0, 0),
		SColor(255,255,255,255), 400.f);

	n = smgr->addBillboardSceneNode(n, dimension2d<f32>(25, 25));
	n->setMaterialFlag(EMF_LIGHTING, false);
	n->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	n->setMaterialTexture(0, driver->getTexture("effects/particlewhite.bmp"));

	while (device->run()) {
		u32 now = device->getTimer()->getTime();
		f32 delta = (f32)(now - then) / 1000.f;
		then = now;
		driver->beginScene(true, true, SColor(255, 20, 20, 20));
		smgr->drawAll();
		driver->endScene();

		player.update(delta);

		int fps = driver->getFPS();
		stringw tmp(L"Flight [");
		tmp += driver->getName();
		tmp += L"] FPS: ";
		if (lastFPS != fps) {
			tmp += fps;
		}
		else tmp += lastFPS;
		tmp += L" X: ";
		tmp += player.node->getPosition().X;
		tmp += L" Y: ";
		tmp += player.node->getPosition().Y;
		tmp += L" Z: ";
		tmp += player.node->getPosition().Z;

		tmp += L" ROTATION X: ";
		tmp += player.node->getRotation().X;
		tmp += L"Y: ";
		tmp += player.node->getRotation().Y;
		tmp += L"Z: ";
		tmp += player.node->getRotation().Z;

		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}
}