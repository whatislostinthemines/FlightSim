#include "ShipMovementSystem.h"

void shipMovementSystem(Scene& scene, f32 dt)
{
	for(auto entityId : SceneView<InputComponent, BulletRigidBodyComponent, IrrlichtComponent>(scene)) {
		BulletRigidBodyComponent* rbc = scene.get<BulletRigidBodyComponent>(entityId);
		InputComponent* input = scene.get<InputComponent>(entityId);
		IrrlichtComponent* irrcomp = scene.get<IrrlichtComponent>(entityId);
		
		f32 maxSpeed = 40.f;
		f32 maxRotSpeed = 100.f;

		vector3df force(0, 0, 0);
		vector3df torque(0, 0, 0);

		//strafing
		if(input->isKeyDown(KEY_KEY_W)) {
			force += irrcomp->getForward() * maxSpeed;
		}
		if(input->isKeyDown(KEY_KEY_S)) {
			force += irrcomp->getBackward() * maxSpeed;
		}
		if(input->isKeyDown(KEY_KEY_A)) {
			force += irrcomp->getLeft() * maxSpeed;
		}
		if(input->isKeyDown(KEY_KEY_D)) {
			force += irrcomp->getRight() * maxSpeed;
		}
		if(input->isKeyDown(KEY_SPACE)) {
			force += irrcomp->getUp() * maxSpeed;
		}
		if(input->isKeyDown(KEY_LCONTROL)) {
			force += irrcomp->getDown() * maxSpeed;
		}

		//rotations
		if(input->isKeyDown(KEY_KEY_Q)) {
			torque += irrcomp->getForward() * maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_E)) {
			torque -= irrcomp->getForward() * maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_R)) {
			torque -= irrcomp->getRight() * maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_F)) {
			torque += irrcomp->getRight() * maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_Z)) {
			torque -= irrcomp->getUp() * maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_C)) {
			torque += irrcomp->getUp() * maxRotSpeed;
		}

		//STOOOOOOOOOOOOOOOOOOOP
		if (input->isKeyDown(KEY_KEY_X)) {
			torque -= bulletVectorToIrrlicht(rbc->rigidBody.getAngularVelocity() * maxRotSpeed);
			force -= bulletVectorToIrrlicht(rbc->rigidBody.getLinearVelocity() * maxSpeed);
		}
		rbc->rigidBody.applyTorqueImpulse(irrlichtVectorToBullet(torque * dt));
		rbc->rigidBody.applyCentralImpulse(irrlichtVectorToBullet(force * dt));
	}
}