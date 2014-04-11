#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "btBulletDynamicsCommon.h"
#include "DMotionState.h"
#include "..\..\Engine\Advanced2D.h"

class GameObject
{
public:
	GameObject(btCollisionShape* pShape, float mass, const btVector3 &color, const btVector3 &initialPosition = btVector3(0,0,0), const btQuaternion &initialRotation = btQuaternion(0,0,1,1));
	~GameObject();

	// 2D Sprite
	void LoadSprite(char *filename);
	void SetSprite(Advanced2D::Sprite *sprite) { m_sprite = sprite; }
	Advanced2D::Sprite* GetSprite() { return m_sprite; }

	// 3D Mesh
	void LoadMesh(char *filename);
	void SetMesh(Advanced2D::Mesh *mesh) { m_mesh = mesh; }
	Advanced2D::Mesh* GetMesh() { return m_mesh; }

	void SetScale(double x, double y, double z);

	// Physics
	btCollisionShape* GetShape() { return m_pShape; }
	btRigidBody* GetRigidBody() { return m_pBody; }
	btMotionState* GetMotionState() { return m_pMotionState; }

	void GetTransform(btScalar* transform)
	{ 
		if (m_pMotionState) m_pMotionState->GetWorldTransform(transform); 
	}
	
	btVector3 GetColor() { return m_color; }

protected:
	Advanced2D::Mesh *m_mesh;
	Advanced2D::Sprite *m_sprite;
	btCollisionShape*  m_pShape;
	btRigidBody*    m_pBody;
	DMotionState*  m_pMotionState;
	btVector3      m_color;
	
};
#endif