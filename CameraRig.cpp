#include "CameraRig.h"
#include "Physics.h"
#include <iostream>
#include <cmath>

f32 clamp(f32 val, f32 min, f32 max)
{
	return std::max(std::min(max, val), min);
}

void CameraRig::moveCamera(RigidBodyComponent body, ISceneNode* node, Directions dir, f32 time)
{
	vector3df up = dir.up;
	vector3df nodeVelocity = body.velocity;
	vector3df nodeAngularVelocity = body.angularVelocity;

	camera->setUpVector(up);
	vector3df target = node->getPosition() + (nodeVelocity * .1f);
	camera->setTarget(target);
}