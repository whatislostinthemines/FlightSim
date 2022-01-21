#include "IrrlichtRigidBodyPositionSystem.h"

void irrlichtRigidBodyPositionSystem(Scene& scene, f32 dt)
{
	for (auto entityId : SceneView<RigidBodyComponent, IrrlichtComponent>(scene)) {

		RigidBodyComponent* rbc = scene.get<RigidBodyComponent>(entityId);
		IrrlichtComponent* irrcomp = scene.get<IrrlichtComponent>(entityId);

		irrcomp->node->setPosition(rbc->position);
		vector3df eulerOrientation;
		rbc->orientation.toEuler(eulerOrientation);
		eulerOrientation = eulerOrientation * RADTODEG;
		irrcomp->node->setRotation(eulerOrientation);
	}
}