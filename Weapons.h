#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

#ifndef WEAPONS_H
#define WEAPONS_H

class Controller;

//might want to make this inherit from rigid physics object base class later?
class Weapon {
	public:
		Weapon();
		Weapon(ISceneNode* node, IMesh* mesh, Controller* cont);

		ISceneNode* wep;
		IMesh* wepMesh;
		Controller* controller;
		void fire(f32 time);
	protected:
		f32 speed = 300.f;
		f32 range = 1500.f;
		f32 fireRate = 1.f;
		f32 timeSinceLastFire = 0.0f;
};

struct Projectile {
	ISceneNode* node;
	vector3df velocity;
};
#endif
