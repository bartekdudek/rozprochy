#pragma once
#include "Header.h"

double fsign(double v);

class Player;
class Team;

class Ball
{
private:
	double x;
	double y;
	double vy;
	double vx;
	double v;
	double angle;
	double direction;
public:
	Ball(double x, double y);

	void MoveBall(Team* redTeam, Team* blueTeam);
	void SetSpeed(double vy, double vx, int direction, bool kicked);

	double GetX();
	double GetY();

	void Kicked();
};

