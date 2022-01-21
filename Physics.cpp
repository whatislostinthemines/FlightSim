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


void checkCollisions(vector<Collider*> colliders)
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

bool collide(SphereColliderComponent sphere, SphereColliderComponent otherSphere) {
	vector3df connectingLine = sphere.center - otherSphere.center;
	f32 sumRadSquared = (sphere.radius + otherSphere.radius) * (sphere.radius + otherSphere.radius);

	return connectingLine.getLengthSQ() < sumRadSquared;
}

bool collide(SphereColliderComponent sphere, AxisAlignedBoundingBoxColliderComponent otherAABB) {
	vector3df closestPoint;

	if (sphere.center.X > otherAABB.max.X) {
		closestPoint.X = otherAABB.max.X;
	}
	else if (sphere.center.X < otherAABB.min.X) {
		closestPoint.X = otherAABB.min.X;
	}
	else {
		closestPoint.X = sphere.center.X;
	}
	if (sphere.center.Y > otherAABB.max.Y) {
		closestPoint.Y = otherAABB.max.Y;
	}
	else if (sphere.center.Y < otherAABB.min.Y) {
		closestPoint.Y = otherAABB.min.Y;
	}
	else {
		closestPoint.Y = sphere.center.Y;
	}
	if (sphere.center.Z > otherAABB.max.Z) {
		closestPoint.Z = otherAABB.max.Z;
	}
	else if (sphere.center.Z < otherAABB.min.Z) {
		closestPoint.Z = otherAABB.min.Z;
	}
	else {
		closestPoint.Z = sphere.center.Z;
	}

	vector3df connectingLine = sphere.center - closestPoint;

	return connectingLine.getLengthSQ() < sphere.radius * sphere.radius;
}
bool collide(SphereColliderComponent sphere, OrientedBoundingBoxColliderComponent otherOBB) {
	vector3df offset = sphere.center - otherOBB.center;
	vector3df pPrime = { offset.dotProduct(otherOBB.axisU), offset.dotProduct(otherOBB.axisV), offset.dotProduct(otherOBB.axisW) };

	f32 sqDist = 0;
	f32 d = 0;

	if (pPrime.X < -otherOBB.hU) {
		d = pPrime.X + otherOBB.hU;
		sqDist += d * d;
	}
	else if (pPrime.X > otherOBB.hU) {
		d = pPrime.X - otherOBB.hU;
		sqDist += d * d;
	}

	if (pPrime.Y < -otherOBB.hV) {
		d = pPrime.Y + otherOBB.hV;
		sqDist += d * d;
	}
	else if (pPrime.Y > otherOBB.hV) {
		d = pPrime.Y - otherOBB.hV;
		sqDist += d * d;
	}

	if (pPrime.Z < -otherOBB.hW) {
		d = pPrime.Z + otherOBB.hW;
		sqDist += d * d;
	}
	else if (pPrime.Z > otherOBB.hW) {
		d = pPrime.Z - otherOBB.hW;
		sqDist += d * d;
	}

	return sqDist <= sphere.radius * sphere.radius;
}

bool collide(SphereColliderComponent sphere, CapsuleColliderComponent otherCapsule) {
	vector3df top = otherCapsule.center + otherCapsule.direction * otherCapsule.height / 2;
	vector3df bottom = otherCapsule.center - otherCapsule.direction * otherCapsule.height / 2;

	vector3df topBottom = bottom - top, topCenter = sphere.center - top, bottomCenter = sphere.center - bottom;

	f32 sqDist;

	f32 e = topBottom.dotProduct(topCenter);
	f32 f = topBottom.getLengthSQ();
	if (e <= f32(0.0f)) {
		sqDist = topCenter.getLengthSQ();
	}
	else if (e >= f) {
		sqDist = bottomCenter.getLengthSQ();
	}
	else {
		sqDist = topCenter.getLengthSQ() - (e * e) / f;
	}

	f32 radius = sphere.radius + otherCapsule.radius;

	return sqDist <= radius * radius;
}

bool collide(AxisAlignedBoundingBoxColliderComponent aABB, SphereColliderComponent otherSphere) {
	return collide(otherSphere, aABB);
}
bool collide(AxisAlignedBoundingBoxColliderComponent aABB, AxisAlignedBoundingBoxColliderComponent otherAABB) {
	return (aABB.min.X <= otherAABB.max.X && aABB.max.X >= otherAABB.min.X) &&
		(aABB.min.Y <= otherAABB.max.Y && aABB.max.Y >= otherAABB.min.Y) &&
		(aABB.min.Z <= otherAABB.max.Z && aABB.max.Z >= otherAABB.min.Z);
}
bool collide(AxisAlignedBoundingBoxColliderComponent aABB, OrientedBoundingBoxColliderComponent otherOBB);
bool collide(AxisAlignedBoundingBoxColliderComponent aABB, CapsuleColliderComponent otherCapsule);

bool collide(OrientedBoundingBoxColliderComponent oBB, SphereColliderComponent otherSphere) {
	collide(otherSphere, oBB);
}
bool collide(OrientedBoundingBoxColliderComponent oBB, AxisAlignedBoundingBoxColliderComponent otherAABB);
bool collide(OrientedBoundingBoxColliderComponent oBB, OrientedBoundingBoxColliderComponent otherOBB);
bool collide(OrientedBoundingBoxColliderComponent oBB, CapsuleColliderComponent otherCapsule);

bool collide(CapsuleColliderComponent capsule, SphereColliderComponent otherSphere) {
	return collide(otherSphere, capsule);
};
bool collide(CapsuleColliderComponent capsule, AxisAlignedBoundingBoxColliderComponent otherAABB);
bool collide(CapsuleColliderComponent capsule, OrientedBoundingBoxColliderComponent otherOBB);
bool collide(CapsuleColliderComponent capsule, CapsuleColliderComponent otherCapsule);