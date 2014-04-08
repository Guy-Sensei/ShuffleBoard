#pragma once
#include "InGameState.h"
class AimState :
	public InGameState
{
public:

	AimState()
	{
	}

	~AimState()
	{
	}

	virtual void HandleInput()
	{
		// receive input to aim left and right, and spacebar to fire
	}

	virtual void Update()
	{
		// show aiming, and power gauge
	}
	virtual void Enter();
	virtual void Exit();

};

