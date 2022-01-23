#include "IrrlichtRigidBodyPositionSystem.h"

void QuaternionToEuler(const btQuaternion& TQuat, btVector3& TEuler) {
	//btScalar W = TQuat.getW();
	//btScalar X = TQuat.getX();
	//btScalar Y = TQuat.getY();
	//btScalar Z = TQuat.getZ();
	//float WSquared = W * W;
	//float XSquared = X * X;
	//float YSquared = Y * Y;
	//float ZSquared = Z * Z;
	btScalar x, y, z;

	TQuat.getEulerZYX(z, y, x);
	TEuler.setValue(x, y, z);
	TEuler *= RADTODEG;

	//TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
	//TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
	//TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
	//TEuler *= RADTODEG;
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