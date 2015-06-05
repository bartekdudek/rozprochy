#ifndef TEAM_H
#define TEAM_H

#include "Header.h"
#include "Player.h"

class Player;
class Team
{
private:
	Player** players;
	Squad team;
	int score;

public:
	Team(Squad t);
	~Team();
	void DrawPlayers();

	int GetScore();
	Player** GetPlayers();
};
#endif
