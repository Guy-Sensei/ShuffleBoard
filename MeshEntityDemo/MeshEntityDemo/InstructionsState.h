//Include Guards
#ifndef INSTRUCTIONSSTATE_H
#define  INSTRUCTIONSSTATE_H

#pragma once
#include "State.h"
#include "InGameState.h"
#include "GameManager.h"
#include "..\..\Engine\Advanced2D.h"
#include "Rock.h"
#include "Player.h"
using namespace Advanced2D;

class GameManager;
class InGameState;

class InstructionsState :
	public State
{
public:
	GameObject *title;
	Camera *camera;
	Vector3 cameraVec;
	Light *light;
	DWORD lastFrameTime;
	DWORD deltaTime;
	DWORD moveTime;
	float dt;
	float previousTime;

	InstructionsState(){};
	InstructionsState(GameManager* manager);
	~InstructionsState(){};
	void HandleInput(int key, inputStates curState);
	void Update();
	void Enter();
	void Exit();
};

#endif

