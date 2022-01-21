#include "PlayerUpdateSystem.h"

void playerUpdateSystem(Scene& scene, f32 dt)
{
	for (auto entityId : SceneView<IrrlichtComponent, PlayerComponent, RigidBodyComponent>(scene)) {
		IrrlichtComponent* irrcomp = scene.get<IrrlichtComponent>(entityId);
		PlayerComponent* player = scene.get<PlayerComponent>(entityId);
		RigidBodyComponent* rbc = scene.get<RigidBodyComponent>(entityId);

		player->camera->setUpVector(irrcomp->getUp());

		vector3df target = irrcomp->node->getPosition() + (rbc->velocity * .1f);
		player->camera->setTarget(target);
	}
}