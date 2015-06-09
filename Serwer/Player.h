#pragma once
#include "Header.h"
#include "Ball.h"

class Team;

class Player
{
private:
	double x;
	double y;
	Squad team;
	double ysign;
	bool horizontally;
	bool kicking;

public:
	Player();
	Player(double x, double y, Squad t);

	double GetX();
	void SetX(double x);

	double GetY();
	void SetY(double y);

	void AddX(double a, Team* red, Team* blue, Ball* ball);
	void AddY(double a, Team* red, Team* blue, Ball* ball);

	void SetHorizontally(bool horizontally, double ysign);

	void Kicked(Ball* ball);

};

