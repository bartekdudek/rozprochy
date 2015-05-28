#pragma once
#include "Header.h"
class Ball
{
private:
	int x;
	int y;
	ALLEGRO_BITMAP* image;
public:
	Ball(int x, int y);
	~Ball();
	void DrawBall();
};

