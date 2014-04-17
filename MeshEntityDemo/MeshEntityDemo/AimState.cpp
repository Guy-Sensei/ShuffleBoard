#include "AimState.h"
#include "ThrowState.h"

AimState::AimState()
{
}

AimState::AimState(GameManager* manager, InGameState *curInGameStateManager)
{
	gm = manager;
	pInGameState = curInGameStateManager;
}

void AimState::HandleInput(int key, inputStates curState)
{
	if (curState == KEYDOWN)
	{
		if(key == DIK_UPARROW || key == DIK_UP)
		{
			pInGameState->incrimentPowerBar();

		}
		if(key == DIK_DOWNARROW || key == DIK_DOWN)
		{
			pInGameState->decrimentPowerBar();
		}
	}	
	if (curState == KEYRELEASE)
	{
		//Jefferson Fraser APR 17
		//Space Bar Feeds into this from the title screen.
		//Need to find way to break key feeding into the next state
		if (key == DIK_LCONTROL)
		{

			
			this->Exit();


		}
	}
}

void AimState::Update()
{
};

void AimState::Enter()
{
	pInGameState->setPowerBarVis(true);
};

void AimState::Exit()
{
	pInGameState->setPowerBarVis(false);
	// pause the rendering engine
	g_engine->setPaused(true);
	PlaySequenceState *temp = new ThrowState(gm, pInGameState);
	pInGameState->playState = temp;
	temp->Enter();
	// restore the rendering engine
	g_engine->setPaused(false);
}