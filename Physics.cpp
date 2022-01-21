#include "Physics.h"
#include <iostream>


void RigidBodyComponent::recalculate() {
	angularVelocity = angularMomentum * inverseInertia;
	orientation.normalize();
	quaternion q(angularVelocity.X, angularVelocity.Y, angularVelocity.Z, 0);
	spin = q * orientation * 0.5f;

	velocity = momentum * inverseMass;
}

void RigidBodyComponent::applyImpulse(vector3df impulse) {
	this->momentum = this->momentum + impulse;
	this->recalculate();
}

void RigidBodyComponent::applyAngularImpulse(vector3df angularImpulse) {
	this->angularMomentum = this->angularMomentum + angularImpulse;
	this->recalculate();
}

void integratePhysicsSystem(Scene& scene, f32 dt) {
	for (auto entityId : SceneView<RigidBodyComponent>(scene)) {
		auto rbc = scene.get<RigidBodyComponent>(entityId);
		rbc->position = rbc->position + rbc->velocity * dt;
		rbc->orientation = rbc->orientation + rbc->spin * dt;
		rbc->orientation = rbc->orientation.normalize();
	}
}
