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
	rbc->transform.setIdentity();
	rbc->transform.setOrigin(irrlichtVectorToBullet(n->getPosition()));

	rbc->motionState = new btDefaultMotionState(rbc->transform);

	aabbox3df bounds = n->getBoundingBox();
	vector3df maxEdge = bounds.MaxEdge;
	vector3df minEdge = bounds.MinEdge;
	btVector3 halves(maxEdge.X - minEdge.X, maxEdge.Y - minEdge.Y, maxEdge.Z - minEdge.Z);
	rbc->shape = new btBoxShape(halves);
	btVector3 localInertia;
	f32 mass = 1.f;
	rbc->shape->calculateLocalInertia(mass, localInertia);
	rbc->rigidBody = new btRigidBody(mass, rbc->motionState, rbc->shape, localInertia);
	world->addRigidBody(rbc->rigidBody);
}