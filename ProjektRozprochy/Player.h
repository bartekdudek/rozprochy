#ifndef PLAYER_H
#define PLAYER_H

#include "Header.h"
#include "Common.h"

class Team;

class Player
{
private:
	double x;
	double y;
	ALLEGRO_BITMAP* image;
	Squad team;
public:
	Player();
	Player(double x, double y, Squad t);
	~Player();
	void Draw();

	double GetX();
	void SetX(double x);

	double GetY();
	void SetY(double y);

	void AddX(double a, Team* red, Team* blue);
	void AddY(double a, Team* red, Team* blue);

};
#endif
