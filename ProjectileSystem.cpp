#include "ProjectileSystem.h"
#include "Controller.h"

void createProjectileEntity(btDiscreteDynamicsWorld* world, Scene& scene, Controller* controller, vector3df spawnPos, vector3df direction, EntityId weaponId)
{
	auto wepInfo = scene.get<WeaponInfoComponent>(weaponId);

	auto projectileEntity = scene.newEntity();
	auto projectileInfo = scene.assign<ProjectileInfoComponent>(projectileEntity);
	projectileInfo->type = wepInfo->type;
	projectileInfo->speed = wepInfo->projectileSpeed;
	projectileInfo->startPos = spawnPos;
	projectileInfo->range = wepInfo->range;

	auto rigidBodyInfo = scene.assign<BulletRigidBodyComponent>(projectileEntity);
	auto irrComp = scene.assign<IrrlichtComponent>(projectileEntity);

	//this needs to be abstracted out to creating different types of node, for now it's just the laser with a crappy particle
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

void destroyProjectile(btDiscreteDynamicsWorld* world, Scene& scene, EntityId projectile)
{
	auto rigidBodyInfo = scene.get<BulletRigidBodyComponent>(projectile);
	world->removeRigidBody(&rigidBodyInfo->rigidBody); //removes the rigid body from the bullet physics

	auto irrComp = scene.get<IrrlichtComponent>(projectile);
	irrComp->node->removeAll(); //removes the children of the node (like particles, billboards etc)
	irrComp->node->remove(); // removes the node

	scene.remove<BulletRigidBodyComponent>(projectile);
	scene.remove<IrrlichtComponent>(projectile);
	scene.remove<ProjectileInfoComponent>(projectile);
	scene.destroyEntity(projectile); //bye bye your life goodbye
}

void projectileRangeSystem(btDiscreteDynamicsWorld* world, Scene& scene)
{
	for (auto id : SceneView<BulletRigidBodyComponent, ProjectileInfoComponent, IrrlichtComponent>(scene)) {
		auto projectileInfo = scene.get<ProjectileInfoComponent>(id);
		auto irr = scene.get<IrrlichtComponent>(id);

		vector3df distance = irr->node->getAbsolutePosition() - projectileInfo->startPos;
		if (distance.getLength() >= projectileInfo->range) {
			destroyProjectile(world, scene, id);
		}
	}
}