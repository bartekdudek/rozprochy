#pragma once
#include "Header.h"

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

	ALLEGRO_BITMAP* image;
public:
	Ball(double x, double y);
	~Ball();
	void DrawBall();
	
	void MoveBall(Team* redTeam, Team* blueTeam);
	void SetSpeed(double vy, double vx, int direction, bool kicked);

	double GetX();
	double GetY();

	void Kicked();
};

