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
	Scene scene;
	sceneECS = SceneManager(scene, this);
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
		/*
		keysDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		if (event.KeyInput.Key == KEY_KEY_Y && !keysDown[KEY_KEY_Y]) {
			setMouseEnabled(!isMouseEnabled());
			std::cout << "Mouse state is " << isMouseEnabled() << std::endl;
		}
		return true;
		*/
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
				input->mousePosition.X = event.MouseInput.X;
				input->mousePosition.Y = event.MouseInput.Y;
				break;
			default:
				break;
			}
		}
		/*
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
			
		}*/
	}
	return false;
}

void Controller::makePlayer()
{
	IAnimatedMesh* playerMesh = smgr->getMesh("models/tux/Tux.obj");
	IAnimatedMeshSceneNode* playerNode = smgr->addAnimatedMeshSceneNode(playerMesh);
	playerNode->setMaterialTexture(0, driver->getTexture("models/tux/BulletShipTex.png"));
	playerNode->setDebugDataVisible(EDS_BBOX);
	//playerNode->setMaterialFlag(EMF_LIGHTING, false);
	ICameraSceneNode* camera = smgr->addCameraSceneNode(playerNode, vector3df(0, 5, -20), playerNode->getPosition(), -1, true);
	//camera->bindTargetAndRotation(true);

	auto playerEntity = sceneECS.scene.newEntity();
	auto rbc = sceneECS.scene.assign<RigidBodyComponent>(playerEntity);
	rbc->position = playerNode->getPosition();
	auto irrComponent = sceneECS.scene.assign<IrrlichtComponent>(playerEntity);
	irrComponent->node = playerNode;
	sceneECS.scene.assign<InputComponent>(playerEntity);

	auto playerCamera = sceneECS.scene.assign<PlayerComponent>(playerEntity);
	playerCamera->camera = camera;

}

void Controller::makeAsteroids()
{

	IAnimatedMesh* asteroidMesh = smgr->getMesh("models/asteroid/Asteroid.obj");
	IAnimatedMeshSceneNode* roidNode = smgr->addAnimatedMeshSceneNode(asteroidMesh, 0, -1, randomVector(), randomRotationVector());

}

void Controller::mainLoop()
{
	makePlayer();
	makeAsteroids();
	ISceneNode* n = smgr->addLightSceneNode(0, vector3df(0, 0, 0),
		SColor(200,200,200,200), 400.f);

	n = smgr->addBillboardSceneNode(n, dimension2d<f32>(25, 25));
	n->setMaterialFlag(EMF_LIGHTING, false);
	n->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	n->setMaterialTexture(0, driver->getTexture("effects/particlewhite.bmp"));

	ITexture* sky = driver->getTexture("effects/starskybox.png");
	smgr->addSkyBoxSceneNode(sky, sky, sky, sky, sky, sky);


	f32 accumulator = 0.0f;
	f32 dt = 0.01f;
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

			/*
			player.update(dt);
			PhysicsSystem::integrate(rigidBodies, dt);

			PhysicsSystem::checkCollisions(colliders);
			*/
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

		/*
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
		*/
		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}
}