#include "Team.h"

Team::Team(enum Squad t)
{
	score = 0;
	team = t;
	players = new Player*[PLAYERS_IN_TEAM];

	int xRightBoundryForRed = WINDOW_WIDTH / 2 - PLAYER_SIZE / 2;

	int xLeftBoundryForBlue = WINDOW_WIDTH / 2 + PLAYER_SIZE / 2;



	int xRand;
	int yRand;

	if (team == red)
	{
		for (int i = 0; i < PLAYERS_IN_TEAM; i++)
		{
			do
			{
				xRand = rand() % WINDOW_WIDTH / 2;
				yRand = rand() % WINDOW_HEIGHT;
			} while (xRand < X_LEFT_BOUNDRY || xRand > xRightBoundryForRed || yRand < Y_UP_BOUNDRY || yRand > Y_DOWN_BOUNDRY);

			players[i] = new Player(xRand, yRand, team);
		}
	}
	else if (team == blue)
	{
		for (int i = 0; i < PLAYERS_IN_TEAM; i++)
		{
			do
			{
				xRand = rand() % WINDOW_WIDTH / 2 + WINDOW_WIDTH / 2;
				yRand = rand() % WINDOW_HEIGHT;
			} while (xRand < xLeftBoundryForBlue || xRand > X_RIGHT_BOUNDRY || yRand < Y_UP_BOUNDRY || yRand > Y_DOWN_BOUNDRY);

			players[i] = new Player(xRand, yRand, team);
		}

	}
}


Team::~Team()
{
	delete[] players;
}

int Team::GetScore()
{
	return score;
}

Player** Team::GetPlayers()
{
	return players;
}
