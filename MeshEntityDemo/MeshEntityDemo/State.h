
//Include Guards
//#ifndef STATE_H
//#define STATE_H
#pragma once
#pragma message ("State is included")
#include "GameManager.h"

//class GameManager;

class State
{
public:
	GameManager *gm;//Reference to GameManager
	enum inputStates{KEYDOWN, KEYRELEASE};
	State(){};
	//State(GameManager& manager){};
	virtual ~State(){};
	virtual void HandleInput(int key, inputStates curState){};
	
	virtual void Update(){};
	virtual void Enter(){};
	virtual void Exit(){};
};

//#endif
