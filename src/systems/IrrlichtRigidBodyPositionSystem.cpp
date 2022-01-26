#include "IrrlichtRigidBodyPositionSystem.h"

void QuaternionToEuler(const btQuaternion& TQuat, btVector3& TEuler) {
	btScalar x, y, z;

	TQuat.getEulerZYX(z, y, x);
	TEuler.setValue(x, y, z);
	TEuler *= RADTODEG;
}

void irrlichtRigidBodyPositionSystem(Scene& scene, f32 dt)
{
	for (auto entityId : SceneView<BulletRigidBodyComponent, IrrlichtComponent>(scene)) {

		BulletRigidBodyComponent* rbc = scene.get<BulletRigidBodyComponent>(entityId);
		IrrlichtComponent* irrcomp = scene.get<IrrlichtComponent>(entityId);

		irrcomp->node->setPosition(bulletVectorToIrrlicht(rbc->rigidBody.getWorldTransform().getOrigin()));
		btVector3 eulerOrientation;
		QuaternionToEuler(rbc->rigidBody.getOrientation(), eulerOrientation);
		irrcomp->node->setRotation(bulletVectorToIrrlicht(eulerOrientation));
	}
}