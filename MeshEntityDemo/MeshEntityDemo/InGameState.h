//Include Guards
#ifndef InGameState_H
#define InGameState_H
#pragma once
#include "State.h"
#include "PlaySequenceState.h"
#include "..\..\Engine\Advanced2D.h"
#include "GameManager.h"
#include "Rock.h"
#include "Player.h"

using namespace Advanced2D;
class GameManager;
class PlaySequenceState;

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
	PlaySequenceState *playState;
	//Jeff: This is related to the powerbar graphic
	//It is orientened from the bottom left of the texture, do not forget this or you will be confused
	GameObject *powerBar;
	int curPowerBarHeight;
	int maxPowerBarHeight;
	const static int initialPowerBarHeight = 25;
	const static int powerBarIncriment = 1;
	const static int powerBar_PosX = 10; //X position of power bar
	const static int powerBar_PosY = 75; //Y position of power bar


	//This is Gui Stuff Related to the Player's Turn
	GameObject *turnGraphic;
	GameObject *p1Graphic;
	GameObject *p2Graphic;
	const static int turnGraphicX = 10;//Distance from right side//Right Align


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
	InGameState(GameManager* manager);
	~InGameState(){};
	void HandleInput(int key, inputStates curState);
	void Update();
	void Enter();
	void Exit();



	//PowerBarRelated
	void setPowerBarVis(bool vis);//Tells wether to draw powerbar

	void DrawAimLine();

	int getPower(){return curPowerBarHeight;}
	void incrimentPowerBar();
	void decrimentPowerBar();
	void ChangePlayerTurn();

	void Throw();
};

#endif

