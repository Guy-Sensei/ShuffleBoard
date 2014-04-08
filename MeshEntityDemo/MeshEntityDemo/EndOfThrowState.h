#pragma once
#include "InGameState.h"
class EndOfThrowState :
	public InGameState
{
public:

	EndOfThrowState()
	{
	}

	~EndOfThrowState()
	{
	}

	virtual void HandleInput()
	{
		// pause and wait for next player to confirm
	}

	virtual void Update();
	virtual void Enter();
	virtual void Exit();

};

