#pragma once

#ifndef IRRLICHTUTILS_H
#define IRRLICHTUTILS_H
#include "BaseHeader.h"

//directions for a given node
vector3df getNodeForward(ISceneNode* node);
vector3df getNodeBackward(ISceneNode* node);
vector3df getNodeLeft(ISceneNode* node);
vector3df getNodeRight(ISceneNode* node);
vector3df getNodeUp(ISceneNode* node);
vector3df getNodeDown(ISceneNode* node);

#endif