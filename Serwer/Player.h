#pragma once
#include "Header.h"

class Player
{
private:
	double x;
	double y;
	Squad team;
public:
	Player();
	Player(double x, double y, Squad t);

	double GetX();
	void SetX(double x);

	double GetY();
	void SetY(double y);

	void AddX(double a);
	void AddY(double a);

};

