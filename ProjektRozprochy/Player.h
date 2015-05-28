#pragma once
#include "Header.h"

class Player
{
private:
	int x;
	int y;
	ALLEGRO_BITMAP* image;
	Squad team;
public:
	Player();
	Player(int x, int y, Squad t);
	~Player();
	void Draw();
};

