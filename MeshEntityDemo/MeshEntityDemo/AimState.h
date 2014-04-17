
//EACH THROW STATE IS INCLUDED IN THE INGAME STATE
//Include Guards
#ifndef AIMSTATE_H
#define AIMSTATE_H
#pragma once
#include "State.h"
#include "PlaySequenceState.h"
#include "InGameState.h"
#include "GameManager.h"
#include "..\..\Engine\Advanced2D.h"
#include "Rock.h"
#include "Player.h"


using namespace Advanced2D;

class GameManager;
class InGameState;

class AimState :
	public PlaySequenceState
{
public:
	AimState();
	AimState(GameManager* manager, InGameState *curInGameStateManager);
	~AimState(){};
	void HandleInput(int key, inputStates curState);
	void Update();
	void Enter();
	void Exit();
};

#endif



