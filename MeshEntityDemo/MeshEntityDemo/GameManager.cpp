#include "GameManager.h"


GameManager::GameManager(void)
{
}


GameManager::~GameManager(void)
{
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
}

void GameManager::InitializePhysics()
{
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
	m_pBroadphase = new btDbvtBroadphase();
	m_pSolver = new btSequentialImpulseConstraintSolver();
	m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);
}

void GameManager::Update(float dt)
{
	if (m_pWorld)
	{
		m_pWorld->stepSimulation(dt * 5000);
	}

	for(GameObjects::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		GameObject* pObj = *i;
		
		btTransform transform = pObj->GetRigidBody()->getWorldTransform();
		btVector3 v = transform.getOrigin();
		Advanced2D::Mesh *mesh = pObj->GetMesh();

		if (mesh)
		{
			mesh->SetPosition(v.x(), v.y(), v.z());
		}
	}
}

void GameManager::DebugRender()
{
	for(GameObjects::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		GameObject* pObj = *i;
		DrawBox(pObj);
	}
}

void GameManager::DrawBox(GameObject *gameObject)
{
	btCollisionShape *shape = gameObject->GetShape();

	if (shape->getShapeType() == BOX_SHAPE_PROXYTYPE)
	{
		btTransform transform = gameObject->GetRigidBody()->getWorldTransform();
		btVector3 v = transform.getOrigin();
		const btBoxShape* box = static_cast<const btBoxShape*>(shape);

		btVector3 halfSize = box->getHalfExtentsWithMargin();

		float halfWidth = halfSize.x();
		float halfHeight = halfSize.y();
		float halfDepth = halfSize.z();

		D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 255, 255);

		LPD3DXLINE line;
		D3DXCreateLine(g_engine->getDevice(), &line);
		D3DXMATRIX cameraProj = m_camera->getViewMatrix() * m_camera->getProjectionMatrix();

		line->SetWidth(1.0f);
		line->Begin();

		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + halfWidth, v.z() + halfDepth, v.x() + halfHeight, v.y() + -halfWidth, v.z() + halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + -halfWidth, v.z() + halfDepth, v.x() + -halfHeight, v.y() + -halfWidth, v.z() + halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + -halfHeight, v.y() + -halfWidth, v.z() + halfDepth, v.x() + -halfHeight, v.y() + halfWidth, v.z() + halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + -halfHeight, v.y() + halfWidth, v.z() + halfDepth, v.x() + halfHeight, v.y() + halfWidth, v.z() + halfDepth);

		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + halfWidth, v.z() + -halfDepth, v.x() + halfHeight, v.y() + -halfWidth, v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + -halfWidth, v.z() + -halfDepth, v.x() + -halfHeight, v.y() + -halfWidth, v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + -halfHeight, v.y() + -halfWidth, v.z() + -halfDepth, v.x() + -halfHeight, v.y() + halfWidth, v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + -halfHeight, v.y() + halfWidth, v.z() + -halfDepth, v.x() + halfHeight, v.y() + halfWidth, v.z() + -halfDepth);

		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + halfWidth, v.z() + halfDepth, v.x() + halfHeight, v.y() + halfWidth, v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + -halfWidth, v.z() + halfDepth, v.x() + halfHeight, v.y() + -halfWidth, v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + -halfHeight, v.y() + halfWidth, v.z() + halfDepth, v.x() + -halfHeight, v.y() + halfWidth, v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + -halfHeight, v.y() + -halfWidth, v.z() + halfDepth, v.x() + -halfHeight, v.y() + -halfWidth, v.z() + -halfDepth);
		line->End();
		line->Release();
	}
}

void GameManager::DrawLine(LPD3DXLINE line, D3DXMATRIX *camProj, D3DCOLOR color, float v1_x, float v1_y, float v1_z, float v2_x, float v2_y, float v2_z)
{
	D3DXVECTOR3 lineSet[] = {D3DXVECTOR3(v1_x, v1_y, v1_z), D3DXVECTOR3(v2_x, v2_y, v2_z)};
	line->DrawTransform(lineSet, 2, camProj, color);
}

GameObject* GameManager::CreateGameObject(btCollisionShape* pShape, 
										  const float &mass, 
										  const btVector3 &color, 
										  const btVector3 &initialPosition, 
										  const btQuaternion &initialRotation) 
{

	GameObject* pObject = new GameObject(pShape, mass, color, initialPosition, initialRotation);
	m_objects.push_back(pObject);

	if (m_pWorld)
		m_pWorld->addRigidBody(pObject->GetRigidBody());

	return pObject;
}