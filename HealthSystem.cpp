#include "HealthSystem.h"
#include <iostream>

void destroyHealthObject(btDiscreteDynamicsWorld* world, Scene& scene, EntityId id)
{
	auto irrComp = scene.get<IrrlichtComponent>(id);
	auto rbc = scene.get<BulletRigidBodyComponent>(id);

	if (irrComp) {
		irrComp->node->removeAll();
		irrComp->node->remove();
	}
	if (rbc) {
		world->removeRigidBody(&rbc->rigidBody);
	}
	scene.destroyEntity(id);
}

void updateHealthSystem(btDiscreteDynamicsWorld* world, Scene& scene)
{
	for (auto id : SceneView<HealthComponent>(scene)) {
		auto hpComp = scene.get<HealthComponent>(id);
		if (hpComp->health <= 0) {
			destroyHealthObject(world, scene, id);
		}
	}
}