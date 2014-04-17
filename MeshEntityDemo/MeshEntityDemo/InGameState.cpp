#include "InGameState.h"
//#include "GameManager.h"

InGameState::InGameState()
{
	lastFrameTime = 0;
	deltaTime = 0;
	moveTime = 0;
}

InGameState::InGameState(GameManager* manager)
{
	gameThrow = 0; 
	//Initialize variables
	gm = manager;
	gm->InitializePhysics();
	lastFrameTime = 0;
	deltaTime = 0;
	moveTime = 0;

	gm->GetAudio()->Load("music.mp3", "music");
	gm->GetAudio()->Play("music");
	//set the camera and perspective
	camera = new Camera();
	degree = -90;
	theta = degree*3.1415/180;
	camera->setPosition(1.0f, 0.0f, 50.0f);
	camera->setTarget(cos(theta)+1, 0.0f, sin(theta)+40);
	camera->Update();

	round_state = 1;
	playerstate = PlayerState::P1;

	gm->SetCamera(camera);

	//create a directional light
	D3DXVECTOR3 pos(10.0f,10.0f,0.0f);
	D3DXVECTOR3 dir(1.0f,1.0f,1.0f);
	light1 = new Light(0, D3DLIGHT_DIRECTIONAL, pos, dir, 100);
	light1->setColor(D3DXCOLOR(1,1,1,1));
	light1->Show();
	g_engine->SetAmbient(D3DCOLOR_RGBA(255,255,255,0));

	D3DXVECTOR3 pos2(1.0f,10.0f,0.0f);
	D3DXVECTOR3 dir2(0.0f,-10.0f,0.0f);
	light2 = new Light(0, D3DLIGHT_SPOT, pos2, dir2, 100);
	light2->setColor(D3DXCOLOR(1,1,1,1));
	//light2->Show();
	//g_engine->SetAmbient(D3DCOLOR_RGBA(255,255,255,0));


	GameObject* ground;	
	ground = gm->CreateGameObject(new btBoxShape(btVector3(1,7,300)), 0, btVector3(1, -10.0f, -270.0f));
	ground->CreateMeshFromShape();

	D3DCOLORVALUE groundColor;
	groundColor.r = 0.5;
	groundColor.g = 0.5;
	groundColor.b = 0.5;
	groundColor.a = 0;
	ground->GetMesh()->SetColour(groundColor, Mesh::MT_DIFFUSE);
	ground->GetMesh()->SetColour(groundColor, Mesh::MT_AMBIENT);
	ground->GetMesh()->SetColour(groundColor, Mesh::MT_SPECULAR);
	ground->GetRigidBody()->setFriction(0.1);
	ground->GetRigidBody()->setRestitution(0.1);

	colorP1.r = 1;
	colorP1.g = 0;
	colorP1.b = 1;
	colorP1.a = 0;

	colorP2.r = 0;
	colorP2.g = 1;
	colorP2.b = 0;
	colorP2.a = 0;

	startPosition = btVector3(2, -8, 20);
	secondPosition = btVector3(0, -8, 20);
	//secondPosition = btVector3(120, 120, 120);


	//direction = btVector3(0, 0, -1);

	for(int i = 0; i < numberThrow; i++)
	{
		if(i%2 == 0) 
			r1[i] = new Rock(colorP1, startPosition);	
		else
			r1[i] = new Rock(colorP2, secondPosition);

		gm->GetObjects()->push_back(r1[i]);

		if (gm->GetWorld())
		{
			gm->GetWorld()->addRigidBody(r1[i]->GetRigidBody());
		}
	}

	//PowerBar Initialization
	powerBar = gm->CreateGameObject("PowerBar.bmp");
	//We are drawing from the bottom left because the bar is drawn upward from the bmp
	maxPowerBarHeight =  powerBar->GetSprite()->GetTexHeight();
	powerBar->GetSprite()->setPosition(10.0,( 10.0 + powerBar->GetSprite()->GetTexHeight()));
	//powerBar->GetSprite()->setPosition(10.0, 300);
	curPowerBarHeight = initialPowerBarHeight;
	powerBar->GetSprite()->setHeight(initialPowerBarHeight);
	//we have to adjust the position of the powerbar as it grows
	powerBar->GetSprite()->setPosition(powerBar_PosX,( powerBar_PosY + powerBar->GetSprite()->GetTexHeight() - powerBar->GetSprite()->getHeight()));
	powerBar->GetSprite()->setBottomLeftOrientation();//We want draw texture from bottom left of the bmp

}

void InGameState::HandleInput(int key, inputStates curState)
{
	if (curState == KEYDOWN)
	{
		if(key == DIK_LEFTARROW)
		{
			if(degree > -180) degree = degree - 2;
		}
		if(key == DIK_RIGHTARROW)
		{
			if(degree < 0) degree = degree + 2;
		}
	}
	if (curState == KEYRELEASE)
	{

		if (key == DIK_ESCAPE)
		{
			gm->DestroyAllObjects();
			g_engine->Close();
		}

		if(key == DIK_SPACE)
		{
			direction = btVector3(camera->getTarget().x - camera->getPosition().x, camera->getTarget().y - camera->getPosition().y, camera->getTarget().z - camera->getPosition().z); //
			btVector3 velocity = direction;
			velocity.normalize();
			velocity *= 10.0f+curPowerBarHeight/10;
			r1[gameThrow]->GetRigidBody()->forceActivationState(ACTIVE_TAG);
			r1[gameThrow]->GetRigidBody()->setLinearVelocity(velocity);
			gameThrow++;
			if(gameThrow == 6) gameThrow = 0;
		}	
		if(key == DIK_UPARROW || key == DIK_UP)
		{
			//Imbedded If: Ask if powerbarfull
			if (curPowerBarHeight < maxPowerBarHeight)
			{
				//incriment powerbar height;
				curPowerBarHeight += powerBarIncriment;
				//Change height of sprite being drawn;
				powerBar->GetSprite()->setHeight(curPowerBarHeight);
				//we have to adjust the position of the powerbar as it grows
				powerBar->GetSprite()->setPosition(powerBar_PosX,( powerBar_PosY + powerBar->GetSprite()->GetTexHeight() - powerBar->GetSprite()->getHeight()));
			}

		}
		if(key == DIK_DOWNARROW || key == DIK_DOWN)
		{
			//Imbedded If: Ask if powerbarempty
			if (curPowerBarHeight > 0)
			{
				//decriment powerbar height;
				curPowerBarHeight -= powerBarIncriment;
				//Change height of sprite being drawn;
				powerBar->GetSprite()->setHeight(curPowerBarHeight);
				//we have to adjust the position of the powerbar as it grows
				powerBar->GetSprite()->setPosition(powerBar_PosX,( powerBar_PosY + powerBar->GetSprite()->GetTexHeight() - powerBar->GetSprite()->getHeight()));
			}
		}
	}

}

void InGameState::DrawAimLine()
{
	LPD3DXLINE line;
	D3DXCreateLine(g_engine->getDevice(), &line);
	

	D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 255, 255);
	D3DXMATRIX cameraProj = camera->getViewMatrix() * camera->getProjectionMatrix();

	line->SetWidth(1.0f);
	line->Begin();

	D3DXVECTOR3 lineSet[2] = {D3DXVECTOR3(camera->getX(), camera->getY(), camera->getZ()), D3DXVECTOR3(camera->getX(), camera->getY(), -100.0f)};
	line->DrawTransform(lineSet, 2, &cameraProj, color);

	line->End();
	line->Release();

	
}

void InGameState::Update()
{
	if(lastFrameTime == 0)
		lastFrameTime = timeGetTime();

	deltaTime = timeGetTime() - lastFrameTime;
	lastFrameTime = timeGetTime();

	//	degree = degree + 1;
	if(degree >= 360) degree = 0;
	theta = degree*3.1415/180;

	
	gm->Update(deltaTime);
	//gm->DebugRender();

	if (gm->GetCamera())
	{
		camera->setTarget(cos(theta)+1, 0, sin(theta)+40);
		camera->Update();
	}

	DrawAimLine();
};

void InGameState::Enter()
{

};

void InGameState::Exit()
{

	delete camera;
	delete light1;
	delete light2;
	gm->DestroyAllObjects();
}