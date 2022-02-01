#include "PlayerUpdateSystem.h"
#include "IrrlichtUtils.h"

#include <iostream>
#include <cmath>

void playerUpdateSystem(Scene& scene, f32 frameDelta)
{
	for (auto entityId : SceneView<IrrlichtComponent, PlayerComponent, BulletRigidBodyComponent>(scene)) {
		IrrlichtComponent* irrcomp = scene.get<IrrlichtComponent>(entityId);
		PlayerComponent* player = scene.get<PlayerComponent>(entityId);
		BulletRigidBodyComponent* rbc = scene.get<BulletRigidBodyComponent>(entityId);
		ISceneNode* node = irrcomp->node;
		ICameraSceneNode* camera = player->camera;
		ISceneNode* targetnode = player->target;

		targetnode->setPosition(node->getPosition());

		quaternion nodeRot(node->getRotation() * DEGTORAD);
		quaternion targetRot(targetnode->getRotation() * DEGTORAD);

		quaternion desiredRot;
		desiredRot = desiredRot.slerp(targetRot, nodeRot, frameDelta*player->slerpFactor);
		vector3df targetRotVec(0, 0, 0);
		desiredRot.toEuler(targetRotVec);
		targetRotVec *= RADTODEG;

		targetnode->setRotation(targetRotVec);

		vector3df targetUp = getNodeUp(targetnode);
		camera->setUpVector(targetUp);
		vector3df target = node->getPosition() + bulletVectorToIrrlicht(rbc->rigidBody.getLinearVelocity()) * player->velocityFactor;
		camera->setTarget(target);
	}
}