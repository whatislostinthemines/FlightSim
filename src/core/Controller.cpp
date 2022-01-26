#include "Controller.h"
#include <iostream>
#include <random>

Controller::Controller(IrrlichtDevice* dev)
{
	device = 0;
	smgr = 0;
	guienv = 0;
	driver = 0;
	lastFPS = -1;
	then = 0;
	bWorld = 0;
	init(dev);
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

	//bullet init
	btBroadphaseInterface* broadPhase = new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000));
	btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
	bWorld = new btDiscreteDynamicsWorld(dispatcher, broadPhase, solver, collisionConfig);
	bWorld->setGravity(btVector3(0, 0, 0));

	Scene scene;
	sceneECS = SceneManager(scene, this, bWorld);
	setDefaults(&sceneECS);
}

bool Controller::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_KEY_INPUT_EVENT) {
		for(auto entityId : SceneView<InputComponent>(sceneECS.scene)) {
			InputComponent* input = sceneECS.scene.get<InputComponent>(entityId);
			input->keysDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			if(event.KeyInput.Key == KEY_KEY_Y && !input->keysDown[KEY_KEY_Y]) {
				input->mouseControlEnabled = !input->mouseControlEnabled;
			}
		}
	}
	if (event.EventType == EET_MOUSE_INPUT_EVENT) {
		for(auto entityId: SceneView<InputComponent>(sceneECS.scene)) {
			InputComponent* input = sceneECS.scene.get<InputComponent>(entityId);
			switch(event.MouseInput.Event) {
			case EMIE_LMOUSE_PRESSED_DOWN:
				input->leftMouseDown = true;
				break;
			case EMIE_LMOUSE_LEFT_UP:
				input->leftMouseDown = false;
				break;
			case EMIE_RMOUSE_PRESSED_DOWN:
				input->rightMouseDown = true;
				break;
			case EMIE_RMOUSE_LEFT_UP:
				input->rightMouseDown = false;
				break;
			case EMIE_MOUSE_MOVED:

				input->mousePosition.X = (event.MouseInput.X - ((f32)driver->getScreenSize().Width * .5f)) / ((f32)driver->getScreenSize().Width * .5f);
				input->mousePosition.Y = (event.MouseInput.Y - ((f32)driver->getScreenSize().Height * .5f)) / ((f32)driver->getScreenSize().Height * .5f);
				break;
			default:
				break;
			}
		}

	}
	if (event.EventType == EET_GUI_EVENT) {
		//handle GUI shit here.
	}
	return false;
}

void Controller::mainLoop()
{
	EntityId playerId = createDefaultShip(&sceneECS, vector3df(0, 0, 0));
	initializeDefaultPlayer(&sceneECS, playerId);
	initializeDefaultRigidBody(&sceneECS, playerId);

	EntityId roidId = createDefaultObstacle(&sceneECS, randomVector());
	initializeDefaultRigidBody(&sceneECS, roidId);
	initializeDefaultHealth(&sceneECS, roidId);

	//make the light node an entity as well
	ISceneNode* n = smgr->addLightSceneNode(0, vector3df(0, 0, 0),
		SColor(200,200,200,200), 400.f);

	n = smgr->addBillboardSceneNode(n, dimension2d<f32>(25, 25));
	n->setMaterialFlag(EMF_LIGHTING, false);
	n->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	n->setMaterialTexture(0, driver->getTexture("effects/particlewhite.bmp"));

	ITexture* sky = driver->getTexture("effects/starskybox.png");
	smgr->addSkyBoxSceneNode(sky, sky, sky, sky, sky, sky);


	f32 accumulator = 0.0f;
	f32 dt = 0.005f;
	f32 t = 0.0f;

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
			sceneECS.update(dt);

			t += dt;
			accumulator -= dt;
		}
		// TODO: need to interpolate the leftover time
		const f32 alpha = accumulator / dt;

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

		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}
}