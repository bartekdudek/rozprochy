#ifndef PLAYER_H
#define PLAYER_H

#include "Header.h"
#include "Ball.h"
#include "Common.h"

class Team;

class Player
{
private:
	ALLEGRO_BITMAP* image;
	Squad team;
	double x;
	double y;
	double ysign;
	bool horizontally;
	bool kicking;

public:
	Player();
	Player(double x, double y, Squad t);
	~Player();
	void Draw();

	double GetX();
	void SetX(double x);

	double GetY();
	void SetY(double y);

	void AddX(double a, Team* red, Team* blue, Ball* ball);
	void AddY(double a, Team* red, Team* blue, Ball* ball);

	void SetHorizontally(bool horizontally, double ysign);

	void Kicked(Ball* ball);

};
#endif
