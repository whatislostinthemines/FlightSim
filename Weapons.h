#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

#ifndef WEAPONS_H
#define WEAPONS_H

class Controller;

class Weapon {
	public:
		ISceneNode* wep;
		IMesh* wepMesh;
		f32 fireRate;
		Controller* controller;
		void fire();
	protected:
};

struct Projectile {
	ISceneNode* node;
	vector3df velocity;
};
#endif
