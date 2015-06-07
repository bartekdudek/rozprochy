#include "Player.h"

volatile int working = 0;

Player::Player()
{
	this->x = 0;
	this->y = 0;
}

Player::Player(double x, double y, Squad t)
{
	team = t;

	this->x = x;
	this->y = y;
}


double Player::GetX()
{
	while (working == 1);
	working = 1;
	working = 0;
	return x;
	
}

void Player::SetX(double x)
{
	while (working == 1);
	working = 1;
	
	if (x > X_RIGHT_BOUNDRY)
		this->x = X_RIGHT_BOUNDRY;
	else if (x < X_LEFT_BOUNDRY)
		this->x = X_LEFT_BOUNDRY;
	else
		this->x = x;
	working = 0;
}

double Player::GetY()
{
	while (working == 1);
	working = 1;
	working = 0;
	return y;
}

void Player::SetY(double y)
{
	while (working == 1);
	working = 1;
	if (y > Y_DOWN_BOUNDRY)
		this->y = Y_DOWN_BOUNDRY;
	else if (y < Y_UP_BOUNDRY)
		this->y = Y_UP_BOUNDRY;
	else
		this->y = y;
	working = 0;
}

void Player::AddX(double a)
{
	while (working == 1);
	working = 1;
	if (x + a > X_RIGHT_BOUNDRY)
		x = X_RIGHT_BOUNDRY;
	else if (x + a < X_LEFT_BOUNDRY)
		x = X_LEFT_BOUNDRY;
	else
		x += a;
	working = 0;
}

void Player::AddY(double a)
{
	while (working == 1);
	working = 1;
	if (y + a > Y_DOWN_BOUNDRY)
		y = Y_DOWN_BOUNDRY;
	else if (y + a < Y_UP_BOUNDRY)
		y = Y_UP_BOUNDRY;
	else
		y += a;
	working = 0;
}