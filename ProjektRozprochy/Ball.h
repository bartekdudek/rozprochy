#pragma once
#include "Header.h"
class Ball
{
private:
	double x;
	double y;
	ALLEGRO_BITMAP* image;
public:
	Ball(double x, double y);
	~Ball();
	void DrawBall();
};

