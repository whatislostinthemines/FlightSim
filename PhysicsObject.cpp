/*
#include "PhysicsObject.h"
#include "Controller.h"

RigidPhysicsObject::RigidPhysicsObject(IAnimatedMesh* nmesh, IAnimatedMeshSceneNode* nnode, f32 mass, f32 inertia, Controller* cont)
{
	mesh = nmesh;
	node = nnode;
	controller = cont;
	velocity = vector3df(0, 0, 0);
	force = vector3df(0, 0, 0);
	torque = vector3df(0, 0, 0);
	rotVelocity = vector3df(0, 0, 0);
	rigidBodyComponent = {
		vector3df(),
		quaternion(node->getRotation() * DEGTORAD),
		node->getPosition(),
		vector3df(),
		quaternion(),
		vector3df(),
		vector3df(),
		mass,
		1 / mass,
		inertia,
		1 / inertia
	};

	collider.aaBoundingBox = node->getTransformedBoundingBox();
	collider.body = &rigidBodyComponent;
}

RigidPhysicsObject::RigidPhysicsObject()
{
	mesh = 0;
	node = 0;
	controller = 0;
	velocity = vector3df(0, 0, 0);
	force = vector3df(0, 0, 0);
	torque = vector3df(0, 0, 0);
	rotVelocity = vector3df(0, 0, 0);
	rigidBodyComponent = {
		vector3df(),
		quaternion(0,1,0,0),
		vector3df(),
		vector3df(),
		quaternion(),
		vector3df(),
		vector3df()
	};

	collider.body = &rigidBodyComponent;
}


//returns a normalized vector for the forward position
//all GetDirection functions are NORMALIZED
vector3df RigidPhysicsObject::getForward()
{
	if (node) {
		vector3df rotation = node->getRotation();
		vector3df forward = vector3df(0, 0, 1);
		return rotation.rotationToDirection(forward);
	}
	return vector3df(0, 0, 0);
}

vector3df RigidPhysicsObject::getBackward()
{
	return -getForward();
}

vector3df RigidPhysicsObject::getLeft()
{
	if (node) {
		vector3df rotation = node->getRotation();
		vector3df left = vector3df(-1, 0, 0);
		return rotation.rotationToDirection(left);
	}
	return vector3df(0, 0, 0);
}

vector3df RigidPhysicsObject::getRight()
{
	return -getLeft();
}

vector3df RigidPhysicsObject::getUp()
{
	if (node) {
		vector3df rotation = node->getRotation();
		vector3df up = vector3df(0, 1, 0);
		return rotation.rotationToDirection(up);
	}
	return vector3df(0, 0, 0);
}

vector3df RigidPhysicsObject::getDown()
{
	return -getUp();
}

void RigidPhysicsObject::posUpdate(f32 time)
{
	//position
	vector3df impulse = force * time;
	Physics::applyImpulse(&rigidBodyComponent, impulse);

	node->setPosition(rigidBodyComponent.position);
	force = vector3df();

	vector3df angularImpulse = torque * time;
	Physics::applyAngularImpulse(&rigidBodyComponent, angularImpulse);
	vector3df eulerOrientation = vector3df();
	rigidBodyComponent.orientation.toEuler(eulerOrientation);
	eulerOrientation = eulerOrientation * RADTODEG;
	node->setRotation(eulerOrientation);
	torque = vector3df();

	collider.aaBoundingBox = node->getTransformedBoundingBox();

}

void RigidPhysicsObject::turnToPos(vector3df pos)
{
	matrix4 localTransform = node->getAbsoluteTransformation(); //transforms global position to local position
	localTransform.makeInverse();
	vector3df localPos = pos;
	localTransform.transformVect(localPos);
	localPos.normalize();
	torque.X += localPos.Y;
	torque.Y -= localPos.X;
}

*/