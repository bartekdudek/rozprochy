#pragma once

#include <stdio.h>
#include <winsock.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

#define PLAYER_SIZE 35
#define BALL_SIZE 35

#define X_RIGHT_BOUNDRY_FOR_RED (WINDOW_WIDTH / 2 - PLAYER_SIZE / 2)

#define X_LEFT_BOUNDRY_FOR_BLUE (WINDOW_WIDTH / 2 + PLAYER_SIZE / 2)

#define PLAYERS_IN_TEAM 2

#define MOVE_CHANGE 0.7
#define MOVE_DELTA 3.5

#define STRING_SIZE 80

#define MINUS_ONE -1.0
#define PLUS_ONE   1.0

#define KICK_CHANGE   1.0
#define KICK_DISTANCE 10.0

#define DIRECTING_COEFF 4.0

enum Squad
{
	red,
	blue,
	SQUAD_NR_ITEMS
};

enum Order
{
	first,
	second,
	third,
	fourth
};

struct Point
{
	double x;
	double y;
};

enum Direction
{
	left,
	right,
	up,
	down
};

enum Direction2
{
	horizontal,
	vertical
};
