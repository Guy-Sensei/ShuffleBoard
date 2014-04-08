#pragma once
#include "MasterGameState.h"
class TitleScreenState :
	public MasterGameState
{
public:
	TitleScreenState();
	~TitleScreenState();
	virtual void HandleInput();
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

