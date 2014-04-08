#pragma once
#include "InGameState.h"
class ThrowState :
	public InGameState
{
public:

	ThrowState()
	{
	}

	~ThrowState()
	{
	}

	virtual void HandleInput()
	{
		// no Input during throw
	}

	virtual void Update();
	virtual void Enter();
	virtual void Exit();

};

