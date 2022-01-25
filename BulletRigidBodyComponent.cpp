#include "BulletRigidBodyComponent.h"

vector3df bulletVectorToIrrlicht(btVector3 vec)
{
	return vector3df(vec.x(), vec.y(), vec.z());
}

btVector3 irrlichtVectorToBullet(vector3df vec)
{
	return btVector3(vec.X, vec.Y, vec.Z);
}

//adds a rigid body component to the given entity based off the irrlicht component associated with that entity
void initializeRigidBodyFromIrrlicht(btDiscreteDynamicsWorld* world, Scene& scene, EntityId id)
{
	IrrlichtComponent* irr = scene.get<IrrlichtComponent>(id);
	BulletRigidBodyComponent* rbc = scene.assign<BulletRigidBodyComponent>(id);

	ISceneNode* n = irr->node;
	btTransform transform = btTransform();
	transform.setIdentity();
	transform.setOrigin(irrlichtVectorToBullet(n->getPosition()));

	auto motionState = new btDefaultMotionState(transform);

	aabbox3df bounds = n->getBoundingBox();
	vector3df maxEdge = bounds.MaxEdge;
	vector3df minEdge = bounds.MinEdge;
	btVector3 halves((maxEdge.X - minEdge.X)*.5f, (maxEdge.Y - minEdge.Y)*.5f, (maxEdge.Z - minEdge.Z)*.5f);
	auto shape = new btBoxShape(halves);
	btVector3 localInertia;
	f32 mass = 1.f;
	shape->calculateLocalInertia(mass, localInertia);
	rbc->rigidBody = btRigidBody(mass, motionState, shape, localInertia);
	rbc->rigidBody.setSleepingThresholds(0, 0);

	rbc->rigidBody.setUserIndex(getEntityIndex(id));
	rbc->rigidBody.setUserIndex2(getEntityVersion(id));
	rbc->rigidBody.setUserIndex3(1);

	world->addRigidBody(&(rbc->rigidBody));
}