#ifndef DXMOTIONSTATE_H
#define DXMOTIONSTATE_H

#include "btBulletCollisionCommon.h"

class DMotionState : public btDefaultMotionState
{
public:
	DMotionState(const btTransform &transform) : btDefaultMotionState(transform) {}
	
	void GetWorldTransform(btScalar* transform)
	{
		btTransform trans;
		getWorldTransform(trans);
		trans.getOpenGLMatrix(transform);
	}
};

#endif