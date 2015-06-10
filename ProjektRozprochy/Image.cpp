#include "Image.h"


Image::Image()
{
	this->bitmap = NULL;
	this->x = 0;
	this->y = 0;
	this->representation = redPlayer;
}

Image::Image(Object r, int s, double x, double y)
{
	this->x = x;
	this->y = y;
	this->representation = r;
	this->size = s;

	if (representation == redPlayer)
		this->bitmap = al_load_bitmap("Resources/redPlayer.png");
	else if (representation == bluePlayer)
		this->bitmap = al_load_bitmap("Resources/bluePlayer.png");
	else if (representation == ball)
		this->bitmap = al_load_bitmap("Resources/ball.png");
	else
		this->bitmap = NULL;

	al_convert_mask_to_alpha(this->bitmap, al_map_rgb(255, 255, 0));

}

Image::~Image()
{
	al_destroy_bitmap(bitmap);
}

void Image::Draw()
{
	double xStart = x - size / 2.0;
	double yStart = y - size / 2.0;

	al_draw_bitmap(bitmap, xStart, yStart, 0);
}

void Image::setX(double x)
{
	this->x = x;
}

void Image::setY(double y)
{
	this->y = y;
}

void Image::updateWithCurrentImage()
{
	if (representation == redPlayer)
	{
		this->bitmap = al_load_bitmap("Resources/currentRedPlayer.png");
		al_convert_mask_to_alpha(this->bitmap, al_map_rgb(255, 255, 0));
	}
	else if (representation == bluePlayer)
	{
		this->bitmap = al_load_bitmap("Resources/currentBluePlayer.png");
		al_convert_mask_to_alpha(this->bitmap, al_map_rgb(255, 255, 0));
	}
	
}
