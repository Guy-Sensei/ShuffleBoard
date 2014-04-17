// Jefferson Fraser
//This Class is supposed to help type differentiation when coding so that we do not mistake what happens during the main game with others
//We do not want to destroy game objects, cameras or lights inbetween throws, so I offer this suggestion.
#ifndef PLAYSEQUENCESTATE_H
#define PLAYSEQUENCESTATE_H
#pragma once
#pragma message ("PLAYSEQUENCE is included")
#include "State.h"
#include "InGameState.h"
#include "GameManager.h"
#include "..\..\Engine\Advanced2D.h"
#include "Rock.h"
#include "Player.h"


using namespace Advanced2D;



class GameManager;
class InGameState;

class PlaySequenceState :
	public State
{
protected:
	// Jefferson Fraser APR 17
	//We include a reference to the game screen for control of cameras and such.
	//Some physics objects must not get destroyed so we add the game states by composition
	InGameState *pInGameState;
public:
	
	PlaySequenceState(){};
	PlaySequenceState(GameManager* manager, InGameState *curInGameStateManager){};
	virtual ~PlaySequenceState(){};
	void HandleInput(int key, inputStates curState){};
	void Update(){};
	void Enter(){};
	void Exit(){};
};

#endif