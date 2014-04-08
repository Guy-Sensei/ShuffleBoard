#pragma once
#include "MasterGameState.h"
class GameOverState :
	public MasterGameState
{
public:
	GameOverState();
	~GameOverState();
	
	virtual void HandleInput()
	{
		// receive input to return to title screen
	}

	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

