#include "PlayerUpdateSystem.h"

void playerUpdateSystem(Scene& scene, f32 dt)
{
	for (auto entityId : SceneView<IrrlichtComponent, PlayerComponent, BulletRigidBodyComponent>(scene)) {
		IrrlichtComponent* irrcomp = scene.get<IrrlichtComponent>(entityId);
		PlayerComponent* player = scene.get<PlayerComponent>(entityId);
		BulletRigidBodyComponent* rbc = scene.get<BulletRigidBodyComponent>(entityId);

		player->camera->setUpVector(irrcomp->getUp());

		vector3df target = irrcomp->node->getPosition() + bulletVectorToIrrlicht(rbc->rigidBody->getLinearVelocity() * .1f);
		player->camera->setTarget(target);
	}
}