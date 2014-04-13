/*
Name: MeshEntityDemo
Date: 25/02/08
Description: Demonstrates managed mesh entities
*/

#include "..\Engine\Advanced2D.h"
#include "MeshEntityDemo\GameManager.h"

using namespace Advanced2D;

GameManager* gm;
Camera *camera;
Vector3 cameraVec;
Light *light;

DWORD lastFrameTime = 0;
DWORD deltaTime = 0;
DWORD moveTime = 0;
float dt;
float previousTime;

D3DCOLORVALUE colorP1;
D3DCOLORVALUE colorP2;
btVector3 startPosition;


int Time()
{
	time_t int_time;
	return time(&int_time);
}

#define MAX 10

void CreateDisc(D3DCOLORVALUE color)
{
	D3DCOLORVALUE discColor;
	discColor.r = 255;
	discColor.g = 100;
	discColor.b = 255;
	discColor.a = 0;

	GameObject* disc;
	disc = gm->CreateGameObject(new btCylinderShape(btVector3(1, 1, 0.1)), 1.0, btVector3(1,1,1), startPosition);
	disc->CreateMeshFromShape();
	disc->GetMesh()->SetColour(discColor, Mesh::MT_DIFFUSE);
	//disc->GetRigidBody()->setAngularFactor(20);
}

bool game_preload() 
{
	g_engine->setAppTitle("MESH ENTITY DEMO");
	g_engine->setFullscreen(false);
	g_engine->setScreenWidth(800);
	g_engine->setScreenHeight(600);
	g_engine->setColorDepth(32);    
	return 1;
}

bool game_init(HWND) 
{
	gm = new GameManager();
	gm->InitializePhysics();

	//set the camera and perspective
	camera = new Camera();
	camera->setPosition(0.0f, 0.0f, 0.0f);
	camera->setTarget(0.0f, 0.0f, 1.0f);
	camera->Update();

	gm->SetCamera(camera);

	//create a directional light
	D3DXVECTOR3 pos(10.0f,10.0f,0.0f);
	D3DXVECTOR3 dir(1.0f,1.0f,1.0f);
	light = new Light(0, D3DLIGHT_DIRECTIONAL, pos, dir, 100);
	light->setColor(D3DXCOLOR(1,1,1,1));
	light->Show();
	g_engine->SetAmbient(D3DCOLOR_RGBA(255,255,255,0));

	GameObject* ground;	
	ground = gm->CreateGameObject(new btBoxShape(btVector3(1,50,30)), 0, btVector3(255.0f, 255.0f, 255.0f), btVector3(40, -10.0f, 0.0f));
	ground->CreateMeshFromShape();

	D3DCOLORVALUE groundColor;
	groundColor.r = 100;
	groundColor.g = 100;
	groundColor.b = 100;
	groundColor.a = 0;
	ground->GetMesh()->SetColour(groundColor, Mesh::MT_DIFFUSE);
	ground->GetMesh()->SetColour(groundColor, Mesh::MT_AMBIENT);
	ground->GetMesh()->SetColour(groundColor, Mesh::MT_SPECULAR);

	colorP1.r = 255;
	colorP1.g = 100;
	colorP1.b = 100;
	colorP1.a = 0;

	colorP2.r = 255;
	colorP2.g = 100;
	colorP2.b = 100;
	colorP2.a = 0;

	startPosition = btVector3(1, 10, 0);

	CreateDisc(colorP1);

	return 1;
}

void game_update() 
{
	if(lastFrameTime == 0)
		lastFrameTime = timeGetTime();

	deltaTime = timeGetTime() - lastFrameTime;
	lastFrameTime = timeGetTime();


	gm->Update(deltaTime);

	if (gm->GetCamera())
	{
		camera->setPosition(camera->getPosition().x + cameraVec.getX(), camera->getPosition().y + cameraVec.getY(), camera->getPosition().z + cameraVec.getZ());
		camera->setTarget(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z - 1.0);
		camera->Update();
		cameraVec = Vector3(0.0, 0.0, 0.0);
	}
}

void Render_Debug()
{
	gm->DebugRender();
}

void game_render3d()
{
	g_engine->ClearScene(D3DCOLOR_RGBA(0,0,60,0));
	g_engine->SetIdentity();
}

void game_keyRelease(int key) 
{ 
	if (key == DIK_ESCAPE) g_engine->Close();

	if (key == DIK_A)
		cameraVec = Vector3(1.0, 0.0, 0.0);

	if (key == DIK_D)
		cameraVec = Vector3(-1.0, 0.0, 0.0);

	if (key == DIK_W)
		cameraVec = Vector3(0.0, 0.0, -1.0);

	if (key == DIK_S)
		cameraVec = Vector3(0.0, 0.0, 1.0);

}

void game_entityUpdate(Advanced2D::Entity* entity) 
{ 
	//static float transUnit = 0.05f;
	//static float maxClamp = 40.0f;
	//   if (entity->getRenderType() == RENDER3D)
	//   {
	//       //type-cast Entity to a Mesh
	//       Mesh* mesh = static_cast<Mesh*>(entity);
	//	if(mesh)
	//	{
	//		//perform a simple rotation
	//		mesh->Rotate(0,0.2f,0);
	//		D3DXVECTOR3 pos = mesh->GetPosition();
	//		pos.z += transUnit;
	//		if(pos.z < maxClamp)
	//			mesh->SetPosition(pos);
	//	}
	//   }
}

void game_entityRender(Advanced2D::Entity* entity) 
{ 
	//type-cast Entity to a Mesh
	Mesh* mesh = (Mesh*)entity;

	//engine automatically renders each entity
	//but we can respond to each render event here
}

void game_end() 
{
	delete camera;
	delete light;
}

void game_render2d() { }
void game_keyPress(int key) { }
void game_mouseButton(int button) { }
void game_mouseMotion(int x,int y) { }
void game_mouseMove(int x,int y) { }
void game_mouseWheel(int wheel) { }
void game_controllerButtonPressed(int index, int button){}
void game_controllerButtonReleased(int index, int button){}
void game_controllerButtonDown(int index, int button){}
void game_controllerLeftTrigger(int index, int value){}
void game_controllerRightTrigger(int index, int value){}
void game_controllerThumbLX(int index, float value){}
void game_controllerThumbLY(int index, float value){}
void game_controllerThumbRX(int index, float value) { }
void game_controllerThumbRY(int index, float value) { }



