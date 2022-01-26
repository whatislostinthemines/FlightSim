#include "WeaponFiringSystem.h"
#include "Controller.h"
#include "SceneManager.h"

void weaponFiringSystem(SceneManager* manager, f32 dt)
{
	Scene* scene = &manager->scene;
	for (auto entityId : SceneView<InputComponent, ShipComponent>(manager->scene)) {
		auto input = scene->get<InputComponent>(entityId);
		auto ship = scene->get<ShipComponent>(entityId);
		if (input->leftMouseDown) {
			for (int i = 0; i < ship->hardpointCount; ++i) {
				EntityId wep = ship->weapons[i];
				auto wepInfo = scene->get<WeaponInfoComponent>(wep);
				wepInfo->isFiring = true;
			}
		}
		else {
			for (int i = 0; i < ship->hardpointCount; ++i) {
				EntityId wep = ship->weapons[i];
				auto wepInfo = scene->get<WeaponInfoComponent>(wep);
				wepInfo->isFiring = false;
			}
		}
	}

	for (auto entityId : SceneView<WeaponInfoComponent, IrrlichtComponent>(manager->scene)) {
		auto wepInfo = scene->get<WeaponInfoComponent>(entityId);
		auto irrComp = scene->get<IrrlichtComponent>(entityId);

		vector3df spawnPos = irrComp->node->getAbsolutePosition() + (irrComp->getForward() * 20.f);

		if (wepInfo->isFiring && (wepInfo->timeSinceLastShot > wepInfo->firingSpeed)) {
			createProjectileEntity(manager, spawnPos, irrComp->getForward(), entityId);
			wepInfo->timeSinceLastShot = 0.f;
		}
		wepInfo->timeSinceLastShot += dt;
	}
}
