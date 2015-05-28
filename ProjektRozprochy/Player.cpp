#include "Player.h"


Player::Player()
{
	this->image = NULL;
	this->x = 0;
	this->y = 0;
}

Player::Player(int x, int y, Squad t)
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
	int xStart = x - PLAYER_SIZE / 2;
	int yStart = y - PLAYER_SIZE / 2;
	al_draw_bitmap(image, xStart, yStart, 0);
}