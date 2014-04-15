#include "InGameState.h"
//#include "GameManager.h"

InGameState::InGameState()
{
	lastFrameTime = 0;
	deltaTime = 0;
	moveTime = 0;
}

InGameState::InGameState(GameManager& manager)
{
	gameThrow = 0; 
	//Initialize variables
	gm = &manager;
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
	ground = gm->CreateGameObject(new btBoxShape(btVector3(1,5,100)), 0, btVector3(255.0f, 255.0f, 255.0f), btVector3(1, -10.0f, 0.0f));
	ground->CreateMeshFromShape();

	D3DCOLORVALUE groundColor;
	groundColor.r = 0.5;
	groundColor.g = 0.5;
	groundColor.b = 0.5;
	groundColor.a = 0;
	ground->GetMesh()->SetColour(groundColor, Mesh::MT_DIFFUSE);
	ground->GetMesh()->SetColour(groundColor, Mesh::MT_AMBIENT);
	ground->GetMesh()->SetColour(groundColor, Mesh::MT_SPECULAR);

	colorP1.r = 1;
	colorP1.g = 0;
	colorP1.b = 1;
	colorP1.a = 0;

	colorP2.r = 0;
	colorP2.g = 1;
	colorP2.b = 0;
	colorP2.a = 0;

	startPosition = btVector3(0, 0, 1);
	//secondPosition = btVector3(120, 120, 120);


	//direction = btVector3(0, 0, -1);

	for(int i = 0; i < numberThrow; i++)
	{
		if(i%2 == 0) 
			r1[i] = new Rock(colorP1, startPosition);	
		else
			r1[i] = new Rock(colorP2, startPosition);
	
		gm->GetObjects()->push_back(r1[i]);
	
		if (gm->GetWorld())
		{
			gm->GetWorld()->addRigidBody(r1[i]->GetRigidBody());
		}
	}
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
			velocity *= 15.0f;
			r1[gameThrow]->GetRigidBody()->setLinearVelocity(velocity);
			gameThrow++;
			if(gameThrow == 7) gameThrow = 6;
		}	
	}

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
	
	
	
	/*
	while(round_state <= ROUND_MAX)
	{
		//while(player2.throw_state <= THROW_MAX)
		{
			if(deltaTime >= 10)
			{
				if(playerstate == PlayerState::P1)
				{
					player1.throw_state++;
					playerstate = PlayerState::P2;
				}
				else
				{
					player2.throw_state++;
					playerstate = PlayerState::P1;
				}
				//deltaTime = 0;
			}
			
		}
		round_state++;
	}
	*/
	gm->Update(deltaTime);

	if (gm->GetCamera())
	{
		camera->setTarget(cos(theta)+1, 0, sin(theta)+40);
		camera->Update();
	}
};

void InGameState::Enter()
{
		//data =  gm->CreateGameObject("title.bmp");
		//data->GetSprite()->setX(50);
		//data->GetSprite()->setY(75);
};

void InGameState::Exit()
{
	delete camera;
	delete light1;
	delete light2;
}