#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Header.h"
#include "Ball.h"
#include "Team.h"

struct dane_dla_watku
{
	SOCKET s;
	int numer;
} dane[PLAYERS_IN_TEAM * 2];

WSADATA wsas;
int result;
WORD wersja;

SOCKET si[PLAYERS_IN_TEAM * 2];
SOCKET s;

struct sockaddr_in sa;
struct sockaddr_in sc;
struct sockaddr_in scomplete[PLAYERS_IN_TEAM*2];

int lenc;
int i;

int order = 0;
struct Point coefficients[4];

Team* redTeam;
Team* blueTeam;

Ball* ball;

HANDLE ghMutex;

bool over = false;
char winningTeam[10];

int redScore;
int blueScore;