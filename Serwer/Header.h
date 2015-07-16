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
 
#define GOAL_DEPTH 35
#define GOAL_WIDTH 142
#define GOAL_UP_POST Y_UP_BOUNDRY + ((Y_DOWN_BOUNDRY-Y_UP_BOUNDRY)/2) - (GOAL_WIDTH/2)
#define GOAL_DOWN_POST Y_UP_BOUNDRY + ((Y_DOWN_BOUNDRY-Y_UP_BOUNDRY)/2) + (GOAL_WIDTH/2)


#define PLAYERS_IN_TEAM 1

#define MOVE_CHANGE 0.7
#define MOVE_CHANGE_KICK MOVE_CHANGE*6.0
#define MOVE_DELTA 3.5
#define SLOWING_BALL_COEFF 1.01

#define STRING_SIZE 80

#define MINUS_ONE -1.0
#define PLUS_ONE   1.0

#define KICK_CHANGE   1.0
#define KICK_DISTANCE 10.0

#define DIRECTING_COEFF 4.0

#define BALL_COUNTER 200

#define WINNING_SCORE 1

#define PORT 50000

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
