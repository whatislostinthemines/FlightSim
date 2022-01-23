#include "WeaponFiringSystem.h"
#include "Controller.h"

void weaponFiringSystem(Scene& scene, btDiscreteDynamicsWorld* world, Controller* controller)
{
	for (auto entityId : SceneView<InputComponent, ShipComponent>(scene)) {
		auto input = scene.get<InputComponent>(entityId);
		auto ship = scene.get<ShipComponent>(entityId);
		if (input->leftMouseDown) {
			for (int i = 0; i < ship->hardpointCount; ++i) {
				EntityId wep = ship->weapons[i];
				auto wepInfo = scene.get<WeaponInfoComponent>(wep);
				wepInfo->isFiring = true;
			}
		}
		else {
			for (int i = 0; i < ship->hardpointCount; ++i) {
				EntityId wep = ship->weapons[i];
				auto wepInfo = scene.get<WeaponInfoComponent>(wep);
				wepInfo->isFiring = false;
			}
		}
	}

	for (auto entityId : SceneView<WeaponInfoComponent, IrrlichtComponent>(scene)) {
		auto wepInfo = scene.get<WeaponInfoComponent>(entityId);
		auto irrComp = scene.get<IrrlichtComponent>(entityId);

		vector3df spawnPos = irrComp->node->getAbsolutePosition() + (irrComp->getForward() * 20.f);

		if (wepInfo->isFiring) {
			createProjectileEntity(world, scene, controller, spawnPos, irrComp->getForward());
		}
	}
}
