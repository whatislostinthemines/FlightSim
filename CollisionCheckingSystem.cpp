#include "CollisionCheckingSystem.h"
#include <iostream>

void collisionCheckingSystem(btDiscreteDynamicsWorld* world, Scene& scene)
{
	int numManifolds = world->getDispatcher()->getNumManifolds();

	for (int i = 0; i < numManifolds; ++i) {
		btPersistentManifold* contact = world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* objA = const_cast<btCollisionObject*>(contact->getBody0());
		btCollisionObject* objB = const_cast<btCollisionObject*>(contact->getBody1());

		EntityIndex indA = objA->getUserIndex();
		EntityVersion verA = objA->getUserIndex2();
		int hasEntA = objA->getUserIndex3();
		EntityId idA = INVALID_ENTITY;
		if (hasEntA) {
			idA = createEntityId(indA, verA);
		}

		EntityIndex indB = objB->getUserIndex();
		EntityVersion verB = objB->getUserIndex2();
		int hasEntB = objB->getUserIndex3();
		EntityId idB = INVALID_ENTITY;
		if (hasEntB) {
			idB = createEntityId(indB, verB);
		}

		ProjectileInfoComponent* projA = nullptr;
		ProjectileInfoComponent* projB = nullptr;
		HealthComponent* hpA = nullptr;
		HealthComponent* hpB = nullptr;

		if (idA != INVALID_ENTITY) {
			projA = scene.get<ProjectileInfoComponent>(idA);
			hpA = scene.get<HealthComponent>(idA);
		}
		
		if (idB != INVALID_ENTITY) {
			projB = scene.get<ProjectileInfoComponent>(idB);
			hpB = scene.get<HealthComponent>(idB);
		}

		//health updates on collision
		if (hpA) {
			if (projB) {
				hpA->health -= projB->damage;
			} // the "else" here should be checking mass and velocity to apply damage if you bonk something super hard
		}
		if (hpB) {
			if (projA) {
				hpB->health -= projB->damage;
			}
		}

		//projectile destruction on collision
		if (projA) {
			destroyProjectile(world, scene, idA);
		}
		if (projB) {
			destroyProjectile(world, scene, idB);
		}
	}
}