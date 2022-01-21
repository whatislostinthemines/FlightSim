#include "Weapons.h"
#include "Controller.h"

vector3df localToGlobal(vector3df localPos, ISceneNode* node)
{
	matrix4 localTransform = node->getAbsoluteTransformation(); 
	localTransform.makeInverse();
	vector3df pos = localPos;
	localTransform.transformVect(pos);
	
	return pos;
}

Weapon::Weapon()
{
	wepMesh = 0;
	wep = 0;
	controller = 0;
}

Weapon::Weapon(ISceneNode* node, IMesh* mesh, Controller* cont)
{
	wepMesh = mesh;
	wep = node;
	controller = cont;
}

void Weapon::fire(f32 time)
{
	vector3df offset = wep->getPosition() + vector3df(0, 0, 2);
	vector3df endPos = offset + vector3df(0, 0, 1500);
	vector3df globalOffset = localToGlobal(offset, wep);
	//to-do: the light scene node should NOT be a child of the weapon

	ISceneNode* projectile = controller->smgr->addLightSceneNode(wep, offset, SColorf(1.f, .3f, .3f, 1.0f), 50.f);
	ISceneNodeAnimator* anim = controller->smgr->createFlyStraightAnimator(offset, endPos, 5000);
	projectile->addAnimator(anim);
	anim->drop();

	ISceneNode* bill = controller->smgr->addBillboardSceneNode(projectile, dimension2d<f32>(5.f, 5.f));
	bill->setMaterialFlag(EMF_LIGHTING, false);
	bill->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	bill->setMaterialTexture(0, controller->driver->getTexture("effects/particlered.bmp"));

	//also to-do: the projectile needs to be deleted when it hits range
}