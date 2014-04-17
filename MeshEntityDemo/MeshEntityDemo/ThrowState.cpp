#include "ThrowState.h"
#include "EndOfThrowState.h"

ThrowState::ThrowState()
{
}

ThrowState::ThrowState(GameManager* manager, InGameState *curInGameStateManager)
{
	gm = manager;
	pInGameState = curInGameStateManager;
}

void ThrowState::HandleInput(int key, inputStates curState)
{
	if (curState == KEYRELEASE)
	{
		//Jefferson Fraser APR 17
		//Replace exit call with some physics event
	
		if (key == DIK_Z)
		{
			this->Exit();

		}
	}
}

void ThrowState::Update()
{
};

void ThrowState::Enter()
{
};

void ThrowState::Exit()
{
	// pause the rendering engine
	g_engine->setPaused(true);
	PlaySequenceState *temp = new EndOfThrowState(gm, pInGameState);
	pInGameState->playState = temp;
	temp->Enter();
	// restore the rendering engine
	g_engine->setPaused(false);
}