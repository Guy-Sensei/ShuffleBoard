#pragma once
class PlayerData
{
public:
	enum PlayerNumber{PlayerOne, PlayerTwo};
	PlayerData(PlayerNumber playerNum);
	~PlayerData(void);
	PlayerNumber getPlayerNumber(){return playerNumber;}

	//Getters
	int getThrowNum(){return throwNumber;}
	int getRoundNumber(){return roundNumber;}
	int getScore(){return score;}

	//Setters
	void setScore(int scoreSet){score = scoreSet;}
	void setRound(int roundSet){roundNumber = roundSet;}
	void setThrowNum(int setthrowNum){throwNumber = setthrowNum;}
private:
	int throwNumber;
	int score;
	int roundNumber;
	PlayerNumber playerNumber;
};

