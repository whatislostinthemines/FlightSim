#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

#ifndef CAMERARIG_H
#define CAMERARIG_H

struct RigidBodyComponent;

struct Directions {
	vector3df forward = vector3df(0, 0, 1);
	vector3df up = vector3df(0, 1, 0);
	vector3df left = vector3df(1, 0, 0);
};

struct CameraRig {
	vector3df offset = vector3df(0, 5, 20);
	ICameraSceneNode* camera;
	void moveCamera(RigidBodyComponent body, ISceneNode* node, Directions dir, f32 time);
};
#endif