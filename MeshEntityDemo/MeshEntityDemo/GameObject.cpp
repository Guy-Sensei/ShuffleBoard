#include "GameObject.h"

GameObject::GameObject(btCollisionShape* pShape, 
					   float mass, 
					   const btVector3 &color, 
					   const btVector3 &initialPosition, 
					   const btQuaternion &initialRotation) 
{
	m_pShape = pShape;
	m_color = color;

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(initialPosition);
	transform.setRotation(initialRotation);

	m_pMotionState = new DMotionState(transform);

	btVector3 localInertia(0,0,0);

	if (mass != 0.0f)
		pShape->calculateLocalInertia(mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, m_pMotionState, pShape, localInertia);

	m_pBody = new btRigidBody(cInfo);

	m_mesh = NULL;
	m_sprite = NULL;
}

void GameObject::LoadMesh(char *filename)
{
	m_mesh = new Advanced2D::Mesh();
	m_mesh->Load(filename);
	m_mesh->setObjectType(Advanced2D::RENDER3D);

	btTransform transform = m_pBody->getWorldTransform();
	btVector3 v = transform.getOrigin();
	m_mesh->SetPosition(v.x(), v.y(), v.z());

	g_engine->addEntity(m_mesh);
}

void GameObject::CreateMeshFromShape()
{
	m_mesh = new Advanced2D::Mesh();
	btTransform transform = m_pBody->getWorldTransform();
	btVector3 v = transform.getOrigin();
	float halfWidth;
	float halfHeight;
	float halfDepth;
	btVector3 halfSize;
	
	switch(m_pShape->getShapeType())
	{
	case CYLINDER_SHAPE_PROXYTYPE:
		//const btCylinderShape* cyl = static_cast<const btCylinderShape*>(m_pShape);
		halfSize = static_cast<const btCylinderShape*>(m_pShape)->getHalfExtentsWithMargin();

		halfWidth = halfSize.x();
		halfHeight = halfSize.y();
		halfDepth = halfSize.z();

		m_mesh->CreateCylinder(halfHeight, halfHeight, halfWidth*2);
		break;

	case BOX_SHAPE_PROXYTYPE:
		//const btBoxShape* box = static_cast<const btBoxShape*>(m_pShape);
		halfSize = static_cast<const btBoxShape*>(m_pShape)->getHalfExtentsWithMargin();

		halfWidth = halfSize.x();
		halfHeight = halfSize.y();
		halfDepth = halfSize.z();

		m_mesh->CreateCube(halfHeight*2, halfWidth*2, halfDepth*2);
		break;
	}

	m_mesh->setObjectType(Advanced2D::RENDER3D);
	m_mesh->SetPosition(v.x(), v.y(), v.z());
	g_engine->addEntity(m_mesh);
}

void GameObject::LoadSprite(char *filename)
{
	m_sprite = new Advanced2D::Sprite();
	m_sprite->loadImage(filename);
	m_sprite->setObjectType(Advanced2D::RENDER2D);

	g_engine->addEntity(m_sprite);
}

GameObject::~GameObject() {
	delete m_pBody;
	delete m_pMotionState;
	delete m_pShape;
}