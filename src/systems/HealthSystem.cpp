#include "HealthSystem.h"
#include "SceneManager.h"
#include <iostream>

void updateHealthSystem(SceneManager* manager)
{
	for (auto id : SceneView<HealthComponent>(manager->scene)) {
		auto hpComp = manager->scene.get<HealthComponent>(id);
		if (hpComp->health <= 0) {
			destroyObject(manager, id);
		}
	}
}