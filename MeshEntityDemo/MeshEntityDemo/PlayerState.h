#pragma once
#include "State.h"
class PlayerState :
	public State
{
public:
	PlayerState();
	~PlayerState();
	virtual void HandleInput();
	virtual void Update();
};

