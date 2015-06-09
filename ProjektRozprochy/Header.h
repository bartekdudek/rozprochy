#pragma once
#include <string>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <winsock.h>

#define WINDOW_WIDTH 982
#define WINDOW_HEIGHT 600

#define PLAYER_SIZE 50
#define BALL_SIZE 35

#define FPS 80.0
#define LPS 25.0 //loads per second

#define STRING_SIZE 80

enum Squad
{
	red,
	blue
};

struct Point
{
	double x;
	double y;
};

enum Object
{
	redPlayer,
	bluePlayer,
	ball
};