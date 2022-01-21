#include "ShipMovementSystem.h"

void shipMovementSystem(Scene& scene, f32 dt)
{
	for(auto entityId : SceneView<InputComponent, RigidBodyComponent, IrrlichtComponent>(scene)) {
		RigidBodyComponent* rbc = scene.get<RigidBodyComponent>(entityId);
		InputComponent* input = scene.get<InputComponent>(entityId);
		IrrlichtComponent* irrcomp = scene.get<IrrlichtComponent>(entityId);
		
		f32 maxSpeed = 40.f;
		f32 maxRotSpeed = 10.f;

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
		if(input->isKeyDown(KEY_CONTROL)) {
			force += irrcomp->getDown() * maxSpeed;
		}

		//rotations
		if(input->isKeyDown(KEY_KEY_Q)) {
			torque.Z += maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_E)) {
			torque.Z -= maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_R)) {
			torque.X -= maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_F)) {
			torque.X += maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_Z)) {
			torque.Y -= maxRotSpeed;
		}
		if(input->isKeyDown(KEY_KEY_C)) {
			torque.Y += maxRotSpeed;
		}

		rbc->applyImpulse(force * dt);
		rbc->applyAngularImpulse(torque * dt);
	}
}