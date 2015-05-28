#include "Ball.h"


Ball::Ball(int x, int y)
{
	this->x = x;
	this->y = y;

	this->image = al_load_bitmap("ball.png");
	al_convert_mask_to_alpha(this->image, al_map_rgb(255, 255, 0));
}


Ball::~Ball()
{
	al_destroy_bitmap(image);
}

void Ball::DrawBall()
{
	int xStart = x - BALL_SIZE / 2;
	int yStart = y - BALL_SIZE / 2;
	al_draw_bitmap(image, xStart, yStart, 0);
}
