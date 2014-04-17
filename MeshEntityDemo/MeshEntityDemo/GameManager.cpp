#include "GameManager.h"


GameManager::GameManager(void)
{
	audio = new Advanced2D::Audio();
	audio->Init();
	m_objects = new GameObjects();
}


//JF: I added this because it would make the GUI math more readable
//EX: 800 -100 
//EX: ScreenW - 100 <--- Programmer knows what sort of math is being done

GameManager::GameManager(const int ScreenW, const int ScreenH)
{
	audio = new Advanced2D::Audio();
	audio->Init();
	m_objects = new GameObjects();

	//Set Screen Height and Width
	screenWidth = ScreenW;
	screenHeight = ScreenH;

}


GameManager::~GameManager(void)
{
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
	DestroyAllObjects();
	delete m_camera;
	delete audio;
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

	for(GameObjects::iterator i = m_objects->begin(); i != m_objects->end(); ++i)
	{
		GameObject* pObj = *i;
		//If the object is not a sprite a physics update is performed
		if (pObj->getIsSprite() == false)
		{
			btTransform transform = pObj->GetRigidBody()->getWorldTransform();
			btVector3 v = transform.getOrigin();
			Advanced2D::Mesh *mesh = pObj->GetMesh();

			if (mesh)
			{
				mesh->SetPosition(v.x(), v.y(), v.z());
			}
		}
	}
}

void GameManager::DebugRender()
{
	for(GameObjects::iterator i = m_objects->begin(); i != m_objects->end(); ++i)
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
	m_objects->push_back(pObject);

	if (m_pWorld)
		m_pWorld->addRigidBody(pObject->GetRigidBody());

	return pObject;
}

void GameManager::DestroyObjectsOfType(Advanced2D::RenderType type)
{
	GameObjects::iterator i = m_objects->begin();
	while(i != m_objects->end())
	{
		GameObject* pObj = *i;
		if(pObj->GetRenderType() == type)
		{
			m_pWorld->removeRigidBody(pObj->GetRigidBody());
			delete pObj;
			i = m_objects->erase(i);
		}

		if(i == m_objects->end() || m_objects->size() == 0)
			break;

		++i;
	}
}

void GameManager::DestroyAllObjects()
{
	for(GameObjects::iterator i = m_objects->begin(); i != m_objects->end(); ++i)
	{
		GameObject* pObj = *i;
		delete pObj;
	}		

	m_objects->clear();
	//g_engine->clearAllEntities();
}

void GameManager::DestroyGameObject(int id)
{

}

GameObject* GameManager::CreateGameObject(char *filename) 
{

	GameObject* pObject = new GameObject(filename);
	m_objects->push_back(pObject);

	return pObject;
}

GameObject* GameManager::CreateGameObject(char *filename, D3DCOLOR transCol)//JF: Needed for Transparency
{

	GameObject* pObject = new GameObject(filename, transCol);
	m_objects->push_back(pObject);

	return pObject;
}

void GameManager::ChangeState(State *newState)
{
	
}