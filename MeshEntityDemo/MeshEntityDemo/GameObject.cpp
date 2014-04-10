#include "GameObject.h"

GameObject::GameObject(btCollisionShape* pShape, float mass, const btVector3 &color, const btVector3 &initialPosition, const btQuaternion &initialRotation) {
	// store the shape for later usage
	m_pShape = pShape;

	// store the color
	m_color = color;

	// create the initial transform
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(initialPosition);
	transform.setRotation(initialRotation);

	// create the motion state from the
	// initial transform
	m_pMotionState = new DMotionState(transform);

	// calculate the local inertia
	btVector3 localInertia(0,0,0);

	// objects of infinite mass can't
	// move or rotate
	if (mass != 0.0f)
		pShape->calculateLocalInertia(mass, localInertia);

	// create the rigid body construction
	// info using the mass, motion state
	// and shape
	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, m_pMotionState, pShape, localInertia);
	
	// create the rigid body
	m_pBody = new btRigidBody(cInfo);

	m_mesh = NULL;
	m_sprite = NULL;
}

void GameObject::SetMesh(Advanced2D::Mesh *mesh)
{
	m_mesh = mesh;
}

void GameObject::SetSprite(Advanced2D::Sprite *sprite)
{
	m_sprite = sprite;
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