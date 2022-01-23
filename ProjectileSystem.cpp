#include "ProjectileSystem.h"
#include "Controller.h"

void createProjectileEntity(btDiscreteDynamicsWorld* world, Scene& scene, Controller* controller, vector3df spawnPos, vector3df direction)
{
	auto projectileEntity = scene.newEntity();
	auto projectileInfo = scene.assign<ProjectileInfoComponent>(projectileEntity);
	projectileInfo->type = WEP_LASER;
	projectileInfo->speed = 100;

	auto rigidBodyInfo = scene.assign<BulletRigidBodyComponent>(projectileEntity);
	auto irrComp = scene.assign<IrrlichtComponent>(projectileEntity);

	irrComp->node = controller->smgr->addLightSceneNode(0, spawnPos, SColorf(.8f, .2f, .2f), 30.f);
	ISceneNode* bill = controller->smgr->addBillboardSceneNode(irrComp->node, dimension2d<f32>(3.f, 3.f));
	bill->setMaterialFlag(EMF_LIGHTING, false);
	bill->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	bill->setMaterialTexture(0, controller->driver->getTexture("effects/particlered.bmp"));

	btTransform transform = btTransform();
	transform.setIdentity();
	transform.setOrigin(irrlichtVectorToBullet(spawnPos));

	auto motionState = new btDefaultMotionState(transform);

	btVector3 halves(1.5f, 1.5f, 1.5f);
	auto shape = new btBoxShape(halves);
	btVector3 localInertia;
	f32 mass = .1f;
	shape->calculateLocalInertia(mass, localInertia);
	rigidBodyInfo->rigidBody = btRigidBody(mass, motionState, shape, localInertia);

	rigidBodyInfo->rigidBody.applyCentralImpulse(irrlichtVectorToBullet(direction) * projectileInfo->speed);

	world->addRigidBody(&rigidBodyInfo->rigidBody);
}