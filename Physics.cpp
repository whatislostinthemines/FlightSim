#include "Physics.h"
#include <iostream>


void RigidBodyComponent::recalculate() {
	angularVelocity = angularMomentum * inverseInertia;
	orientation.normalize();
	quaternion q(angularVelocity.X, angularVelocity.Y, angularVelocity.Z, 0);
	spin = q * orientation * 0.5f;

	velocity = momentum * inverseMass;
}

void Physics::integrate(vector<RigidBodyComponent*> rigidBodies, f32 dt) {
	
	for (RigidBodyComponent* rbc : rigidBodies) {
		rbc->position = rbc->position + rbc->velocity * dt;
		rbc->orientation = rbc->orientation + rbc->spin * dt;
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

void Physics::checkCollisions(vector<Collider*> colliders)
{
	for (int i = 0; i < colliders.size(); ++i) {
		for (int j = 0; j < colliders.size(); ++j) {
			if (i == j) continue;
			if (colliders[j]->aaBoundingBox.intersectsWithBox(colliders[i]->aaBoundingBox)) {
				std::cout << "Collision detected! " << std::endl;
			}
		}
	}
}