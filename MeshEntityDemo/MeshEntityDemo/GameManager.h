#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#pragma once

#include "..\..\Engine\Advanced2D.h"
#include "..\..\Common\BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "GameObject.h"
#include <vector>

typedef std::vector<GameObject*> GameObjects;

class State;

class GameManager
{
public:
	GameManager(void);
	GameManager(const int ScreenW = 800, const int ScreenH = 600);
	~GameManager(void);

	void InitializePhysics();
	GameObject* CreateGameObject(btCollisionShape* pShape, 
		const float &mass, 
		const btVector3 &initialPosition = btVector3(0.0f,0.0f,0.0f), 
		const btQuaternion &initialRotation = btQuaternion(0,0,1,1));

	GameObject* CreateGameObject(char *filename);
	GameObject* CreateGameObject(char *filename, D3DCOLOR transCol);//JF: Needed for Transparency

	btDynamicsWorld* GetWorld() { return m_pWorld; }
	GameObjects* GetObjects() { return m_objects; }


	void DestroyGameObject(int id);
	void DestroyObjectsOfType(Advanced2D::RenderType type);
	void DestroyAllObjects();
	void Update(float dt);
	Advanced2D::Camera* GetCamera() { return m_camera; }
	Advanced2D::Audio* GetAudio() { return audio; }
	void SetCamera(Advanced2D::Camera* cam) { m_camera = cam; }
	void DebugRender();

	State *GetState(){return gameState;}
	void SetState(State *newState){gameState = newState;}
	void ChangeState (State *newstate);
	//void DrawLine(LPD3DXLINE line, D3DXMATRIX *camProj, D3DCOLOR color, float v1_x, float v1_y, float v1_z, float v2_x, float v2_y, float v2_z);

	int GetScreenW() {return screenWidth;}
	int GetScreenH() {return screenHeight;}
private:

	GameObjects* m_objects;
	State *gameState;
	Advanced2D::Camera *m_camera;

	Advanced2D::Audio* audio;
	// Bullet components
	btBroadphaseInterface* m_pBroadphase;
	btCollisionConfiguration* m_pCollisionConfiguration;
	btCollisionDispatcher* m_pDispatcher;
	btConstraintSolver* m_pSolver;
	btDynamicsWorld* m_pWorld;

	void DrawBox(GameObject *gameObject);

	void DrawLine(LPD3DXLINE line, D3DXMATRIX *camProj, D3DCOLOR color, float v1_x, float v1_y, float v1_z, float v2_x, float v2_y, float v2_z);
	int screenWidth;
	int screenHeight;

	


};

#endif