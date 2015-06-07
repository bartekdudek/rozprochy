#pragma once
#include "Header.h"
#include "Player.h"

class Team
{
private:
	Player** players;
	Squad team;
	int score;

public:
	Team(Squad t);
	~Team();

	int GetScore();
	Player** GetPlayers();
};
