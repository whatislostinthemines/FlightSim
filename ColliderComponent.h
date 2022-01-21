#pragma once

#ifndef COLLIDER_H
#define COLLIDER_H
#include <irrlicht.h>

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

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