#include "Player.h"


Player::Player()
{
	this->image = NULL;
	this->x = 0;
	this->y = 0;
}

Player::Player(double x, double y, Squad t)
{
	team = t;
	if (team == red)
		this->image = al_load_bitmap("redPlayer.png");
	else if (team == blue)
		this->image = al_load_bitmap("bluePlayer.png");
	al_convert_mask_to_alpha(this->image, al_map_rgb(255, 255, 0));

	this->x = x;
	this->y = y;
}

Player::~Player()
{
	al_destroy_bitmap(image);
}

void Player::Draw()
{
	double xStart = x - PLAYER_SIZE / 2.0;
	double yStart = y - PLAYER_SIZE / 2.0;
	al_draw_bitmap(image, xStart, yStart, 0);
}

double Player::GetX()
{
	return x;
}

void Player::SetX(double x)
{
	if (x > X_RIGHT_BOUNDRY)
		this->x = X_RIGHT_BOUNDRY;
	else if (x < X_LEFT_BOUNDRY)
		this->x = X_LEFT_BOUNDRY;
	else
		this->x = x;
}

double Player::GetY()
{
	return y;
}

void Player::SetY(double y)
{
	if (y > Y_DOWN_BOUNDRY)
		this->y = Y_DOWN_BOUNDRY;
	else if (y < Y_UP_BOUNDRY)
		this->y = Y_UP_BOUNDRY;
	else
		this->y = y;
}

void Player::AddX(double a)
{
	if (x + a > X_RIGHT_BOUNDRY)
		x = X_RIGHT_BOUNDRY;
	else if (x + a < X_LEFT_BOUNDRY)
		x = X_LEFT_BOUNDRY;
	else
		x += a;
}

void Player::AddY(double a)
{
	if (y + a > Y_DOWN_BOUNDRY)
		y = Y_DOWN_BOUNDRY;
	else if (y + a < Y_UP_BOUNDRY)
		y = Y_UP_BOUNDRY;
	else
		y += a;
}