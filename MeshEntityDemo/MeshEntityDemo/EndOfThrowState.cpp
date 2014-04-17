#include "EndOfThrowState.h"
#include "AimState.h"

EndOfThrowState::EndOfThrowState()
{
}

EndOfThrowState::EndOfThrowState(GameManager* manager, InGameState *curInGameStateManager)
{
	gm = manager;
	pInGameState = curInGameStateManager;
}

void EndOfThrowState::HandleInput(int key, inputStates curState)
{
	if (curState == KEYRELEASE)
	{
			//Jefferson Fraser APR 17
			//Replace exit call with some physics event
	
		if (key == DIK_X)
		{
			this->Exit();

		}
	}
}

void EndOfThrowState::Update()
{
};

void EndOfThrowState::Enter()
{
};

void EndOfThrowState::Exit()
{
	// pause the rendering engine
	g_engine->setPaused(true);
	PlaySequenceState *temp = new AimState(gm, pInGameState);
	pInGameState->playState = temp;
	temp->Enter();
	// restore the rendering engine
	g_engine->setPaused(false);
}
