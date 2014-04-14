#pragma once

//enum GameThrow {DEFAULT, THROW1, THROW2, THROW3, MX};//

class Player
{
public:

	int score;
	//GameThrow throw_state;
	int throw_state;
	
	Player()
	{
		score = 0;
		//throw_state = GameThrow::DEFAULT;
		throw_state = 1;
	}

	~Player()
	{
	}
};

