#pragma once
#include "Header.h"
class Image
{
private:
	Object representation;
	double x;
	double y;
	int size;
	ALLEGRO_BITMAP* bitmap;
public:
	Image();
	Image(Object r, int s, double x = 0, double y = 0);

	void updateWithCurrentImage();

	void Draw();

	void setX(double x);
	void setY(double y);

	~Image();
};

