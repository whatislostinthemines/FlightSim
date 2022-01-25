#include "CollisionCheckingSystem.h"
#include <iostream>

void collisionCheckingSystem(btDiscreteDynamicsWorld* world, Scene& scene)
{
	int numManifolds = world->getDispatcher()->getNumManifolds();

	for (int i = 0; i < numManifolds; ++i) {
		btPersistentManifold* contact = world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* objA = const_cast<btCollisionObject*>(contact->getBody0());
		btCollisionObject* objB = const_cast<btCollisionObject*>(contact->getBody1());
		std::cout << "Collision" << std::endl;
		EntityId idA = objA->getUserIndex();
		EntityId idB = objB->getUserIndex();

		ProjectileInfoComponent* projA = scene.get<ProjectileInfoComponent>(idA);
		ProjectileInfoComponent* projB = scene.get<ProjectileInfoComponent>(idB);

		if (projA) {
			destroyProjectile(world, scene, idA);
		}
		if (projB) {
			destroyProjectile(world, scene, idB);
		}
	}
}