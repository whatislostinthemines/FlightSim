#include "Physics.h"



void RigidBodyComponent::recalculate() {
	angularVelocity = angularMomentum * inverseInertia;
	orientation.normalize();
	quaternion q(0, angularVelocity.X, angularVelocity.Y, angularVelocity.Z);
	spin = q * orientation * 0.5f;

	velocity = momentum * inverseMass;
}

void Physics::integrate(vector<RigidBodyComponent*> rigidBodies, f32 dt) {
	
	for (RigidBodyComponent* rbc : rigidBodies) {
		rbc->position = rbc->position + rbc->velocity * dt;
		rbc->orientation = rbc->orientation + rbc->angularVelocity * dt;
		rbc->orientation = rbc->orientation.normalize();
	}
}

void Physics::applyImpulse(RigidBodyComponent* rigidBody, vector3df impulse) {
	rigidBody->momentum = rigidBody->momentum + impulse;
	rigidBody->recalculate();
}

void Physics::applyAngularImpulse(RigidBodyComponent* rigidBody, vector3df angularImpulse) {
	rigidBody->angularMomentum = rigidBody->angularMomentum + angularImpulse;
	rigidBody->recalculate();
}