#pragma once
#include "MasterGameState.h"
class InGameState :
	public MasterGameState
{
public:
	InGameState();
	~InGameState();
	virtual void HandleInput();
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

