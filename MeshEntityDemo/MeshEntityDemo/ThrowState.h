//EACH THROW STATE IS INCLUDED IN THE INGAME STATE
//Include Guards
#ifndef THROWSTATE_H
#define THROWSTATE_H
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

class ThrowState :
	public PlaySequenceState
{
public:
	ThrowState();
	ThrowState(GameManager* manager, InGameState *curInGameStateManager);
	~ThrowState(){};
	void HandleInput(int key, inputStates curState);
	void Update();
	void Enter();
	void Exit();
};

#endif


