#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


#define WINDOW_WIDTH 982
#define WINDOW_HEIGHT 600

#define COURT_WIDTH 982
#define COURT_HEIGHT 486

#define PLACE_TO_PLAY_WIDTH 850
#define PLACE_TO_PLAY_HEIGHT 390

#define X_LEFT_BOUNDRY ((WINDOW_WIDTH - PLACE_TO_PLAY_WIDTH) / 2 + PLAYER_SIZE / 2)
#define X_RIGHT_BOUNDRY (WINDOW_WIDTH - ((WINDOW_WIDTH - PLACE_TO_PLAY_WIDTH) / 2) - PLAYER_SIZE / 2)

#define Y_UP_BOUNDRY (WINDOW_HEIGHT - COURT_HEIGHT + (COURT_HEIGHT - PLACE_TO_PLAY_HEIGHT) / 2 + PLAYER_SIZE / 2)
#define Y_DOWN_BOUNDRY (WINDOW_HEIGHT - ((COURT_HEIGHT - PLACE_TO_PLAY_HEIGHT) / 2) - PLAYER_SIZE / 2)

#define PLAYER_SIZE 50
#define BALL_SIZE 35

#define PLAYERS_IN_TEAM 2

#define FPS 140.0

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