#include "Controller.h"
#include <iostream>
#include <random>

Controller::Controller(IrrlichtDevice* dev)
{
	player = Player();
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
	return keysDown[key];
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

		if (event.KeyInput.Key == KEY_KEY_Y && !keysDown[KEY_KEY_Y]) {
			setMouseEnabled(!isMouseEnabled());
			std::cout << "Mouse state is " << isMouseEnabled() << std::endl;
		}
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
	IAnimatedMesh* playerMesh = smgr->getMesh("models/tux/Tux.obj");
	IAnimatedMeshSceneNode* playerNode = smgr->addAnimatedMeshSceneNode(playerMesh);
	playerNode->setMaterialTexture(0, driver->getTexture("models/tux/BulletShipTex.png"));
	//playerNode->setMaterialFlag(EMF_LIGHTING, false);
	ICameraSceneNode* camera = smgr->addCameraSceneNode(playerNode, vector3df(0, 5, -20), playerNode->getPosition(), PLAYER_CAMERA, true);
	//camera->bindTargetAndRotation(true);
	Ship* pShip = new Ship(playerMesh, playerNode, 1, 1, this);
	player = Player(pShip, camera, this);
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
		SColor(200,200,200,200), 400.f);

	n = smgr->addBillboardSceneNode(n, dimension2d<f32>(25, 25));
	n->setMaterialFlag(EMF_LIGHTING, false);
	n->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	n->setMaterialTexture(0, driver->getTexture("effects/particlewhite.bmp"));

	f32 accumulator = 0.0f;
	f32 dt = 0.01f;
	f32 t = 0.0f;

	vector<RigidBodyComponent*> rigidBodies = vector<RigidBodyComponent*>();
	rigidBodies.push_back(&player.ship->rigidBodyComponent);
	while (device->run()) {
		u32 now = device->getTimer()->getTime();
		f32 delta = (f32)(now - then) / 1000.f;
		// don't simulate more than a quarter second, arbitrary number but we need an upper bound or else the sim explodes -- if fps drops below 4 you might wanna re-evaluate whatever you just changed
		if (delta > 0.25) {
			delta = 0.25;
		}

		then = now;

		accumulator += delta;
		
		while (accumulator >= dt) {
			// Game logic and physics
			player.update(dt);
			Physics::integrate(rigidBodies, dt);
			t += dt;
			accumulator -= dt;
		}

		const f32 alpha = accumulator / dt;

		// interpolate any remaining time to smooth out frames in between physics steps

		//player.update(delta);


		driver->beginScene(true, true, SColor(255, 20, 20, 20));
		smgr->drawAll();
		driver->endScene();

		int fps = driver->getFPS();
		stringw tmp(L"Flight [");
		tmp += driver->getName();
		tmp += L"] FPS: ";
		if (lastFPS != fps) {
			tmp += fps;
		}
		else tmp += lastFPS;

		vector3df playerPos = player.ship->node->getPosition();
		vector3df playerRot = player.ship->node->getRotation();
		tmp += L" X: ";
		tmp += playerPos.X;
		tmp += L" Y: ";
		tmp += playerPos.Y;
		tmp += L" Z: ";
		tmp += playerPos.Z;

		tmp += L" ROTATION X: ";
		tmp += playerRot.X;
		tmp += L"Y: ";
		tmp += playerRot.Y;
		tmp += L"Z: ";
		tmp += playerRot.Z;

		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}
}