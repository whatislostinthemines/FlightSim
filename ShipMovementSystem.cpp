#include "ShipMovementSystem.h"

void shipMovementSystem(Scene& scene, f32 dt)
{
	for(auto entityId : SceneView<InputComponent, BulletRigidBodyComponent>(scene)) {
		BulletRigidBodyComponent* rbc = scene.get<BulletRigidBodyComponent>(entityId);
		InputComponent* input = scene.get<InputComponent>(entityId);		
		f32 maxSpeed = 40.f;
		f32 maxRotSpeed = 100.f;


		btVector3 torque(0, 0, 0);
		btVector3 force(0, 0, 0);

		btVector3 forward(0, 0, 1);
		btVector3 right(1, 0, 0);
		btVector3 up(0, 1, 0);
		btQuaternion transRot = rbc->rigidBody.getCenterOfMassTransform().getRotation();
		
		forward = forward.rotate(transRot.getAxis(), transRot.getAngle());
		right = right.rotate(transRot.getAxis(), transRot.getAngle());
		up = up.rotate(transRot.getAxis(), transRot.getAngle());

		//strafing
		if(input->isKeyDown(KEY_KEY_W)) {
			//force += irrcomp->getForward() * maxSpeed;
			force += forward * maxSpeed;
		}
		if(input->isKeyDown(KEY_KEY_S)) {
			force -= forward * maxSpeed;
		}
		if(input->isKeyDown(KEY_KEY_A)) {
			force -= right * maxSpeed;
		}
		if(input->isKeyDown(KEY_KEY_D)) {
			force += right * maxSpeed;
		}
		if(input->isKeyDown(KEY_SPACE)) {
			force += up * maxSpeed;
		}
		if(input->isKeyDown(KEY_LCONTROL)) {
			force -= up * maxSpeed;
		}

		//rotations
		if(input->isKeyDown(KEY_KEY_Q)) {
			torque += forward * maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_E)) {
			torque -= forward * maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_R)) {
			torque -= right * maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_F)) {
			torque += right * maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_Z)) {
			torque -= up * maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_C)) {
			torque += up * maxRotSpeed;
		}

		//STOOOOOOOOOOOOOOOOOOOP
		if (input->isKeyDown(KEY_KEY_X)) {
			torque -= rbc->rigidBody.getAngularVelocity() * maxRotSpeed;
			force -= rbc->rigidBody.getLinearVelocity() * maxSpeed;
		}
		rbc->rigidBody.applyTorqueImpulse(torque * dt);
		rbc->rigidBody.applyCentralImpulse(force * dt);
	}
}