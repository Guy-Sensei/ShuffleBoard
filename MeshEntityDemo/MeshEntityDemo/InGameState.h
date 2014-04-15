//Include Guards
#ifndef InGameState_H
#define InGameState_H
#pragma once
#include "State.h"
#include "..\..\Engine\Advanced2D.h"
#include "GameManager.h"
#include "Rock.h"
#include "Player.h"

using namespace Advanced2D;
class GameManager;

class InGameState :
	 public State
{
public:
	GameObject *data;
	Audio* audio;
	GameManager* gm;
	Camera *camera;
	Vector3 cameraVec;
	Light *light1;
	Light *light2;

	static const int numberThrow = 6; 

	Rock* r1[numberThrow];
	Rock* r2;
	btVector3 direction;

	DWORD lastFrameTime;
	DWORD deltaTime;
	DWORD moveTime;
	float dt;
	float previousTime;

	int degree;
	double theta;

	//enum GameRound {DEFAULT, ROUND1, ROUND2, ROUND3, MX};
	//GameRound round_state;
	int round_state;
	static const int ROUND_MAX = 3;
	static const int THROW_MAX = 3;


	enum PlayerState{P1, P2};
	PlayerState playerstate;

	Player player1;
	Player player2;

	D3DCOLORVALUE colorP1;
	D3DCOLORVALUE colorP2;
	btVector3 startPosition;
	btVector3 secondPosition;

	int gameThrow;
	InGameState();
	InGameState(GameManager& manager);
	~InGameState(){};
	void HandleInput(int key, inputStates curState);
	void Update();
	void Enter();
	void Exit();
};

#endif

