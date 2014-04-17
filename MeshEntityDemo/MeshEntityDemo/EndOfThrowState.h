//EACH THROW STATE IS INCLUDED IN THE INGAME STATE
//Include Guards
#ifndef ENDOFTHROWSTATE_H
#define ENDOFTHROWSTATE_H
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

class EndOfThrowState :
	public PlaySequenceState
{
public:
	EndOfThrowState();
	EndOfThrowState(GameManager* manager, InGameState *curInGameStateManager);
	~EndOfThrowState(){};
	void HandleInput(int key, inputStates curState);
	void Update();
	void Enter();
	void Exit();
};

#endif

