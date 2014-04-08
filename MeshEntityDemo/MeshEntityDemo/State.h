#pragma once
class State
{
public:
	State();
	virtual ~State();
	virtual void HandleInput();
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

