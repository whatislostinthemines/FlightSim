#pragma once

#ifndef COLLIDER_H
#define COLLIDER_H
#include "BaseHeader.h"

//code here


struct SphereColliderComponent {
	vector3df center;
	f32 radius;
};

struct AxisAlignedBoundingBoxColliderComponent {
	vector3df min;
	vector3df max;
};

struct OrientedBoundingBoxColliderComponent {
	vector3df center;
	vector3df axisU;
	vector3df axisV;
	vector3df axisW;
	f32 hU;
	f32 hV;
	f32 hW;
};

struct CapsuleColliderComponent {
	vector3df direction;
	vector3df center;
	f32 radius;
	f32 height;
};

// Composite

// Mesh

#endif