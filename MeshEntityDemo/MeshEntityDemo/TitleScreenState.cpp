#include "TitleScreenState.h"


TitleScreenState::TitleScreenState(GameManager* manager)
{
	gm = manager;
	//set the camera and perspective
	camera = new Camera();
	camera->setPosition(0.0f, 2.0f, 50.0f);
	camera->setTarget(0.0f, 0.0f, 0.0f);
	camera->Update();

	gm->SetCamera(camera);

	//create a directional light
	D3DXVECTOR3 pos(0.0f,0.0f,0.0f);
	D3DXVECTOR3 dir(1.0f,1.0f,1.0f);
	light = new Light(0, D3DLIGHT_DIRECTIONAL, pos, dir, 100);
	light->setColor(D3DXCOLOR(1,1,1,1));

	g_engine->SetAmbient(D3DCOLOR_RGBA(255,255,255,0));
}

void TitleScreenState::HandleInput(int key, inputStates curState)
{
	if (curState == KEYDOWN)
	{
		if (key == DIK_SPACE)
		{
			// pause the rendering engine
			g_engine->setPaused(true);

			// call exit function on this state
			this->Exit();

			// Destroy all objects
			gm->DestroyAllObjects();

			// change the state
			InGameState *tempstate = new InGameState(gm);
			State *newState = tempstate;
			gm->SetState(newState);

			// call the Enter function of the new state
			gm->GetState()->Enter();

			// resume rendering engine
			g_engine->setPaused(false);
		}
	}
}

void TitleScreenState::Enter()
{

	title =  gm->CreateGameObject("title.bmp");
};

void TitleScreenState::Update()
{

	if(lastFrameTime == 0)
		lastFrameTime = timeGetTime();
	deltaTime = timeGetTime() - lastFrameTime;
	lastFrameTime = timeGetTime();


	//gm->Update(deltaTime);

	if (gm->GetCamera())
	{
		camera->setPosition(camera->getPosition().x + cameraVec.getX(), camera->getPosition().y + cameraVec.getY(), camera->getPosition().z + cameraVec.getZ());
		camera->setTarget(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z - 1.0);
		camera->Update();
		cameraVec = Vector3(0.0, 0.0, 0.0);
	}

}

void TitleScreenState::Exit()
{

	//delete camera;
	//delete light;
	gm->DestroyAllObjects();
}

