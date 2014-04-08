#pragma once
#include "State.h"
class MasterGameState :
	public State
{
public:
	MasterGameState();
	~MasterGameState();
	virtual void HandleInput();
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

