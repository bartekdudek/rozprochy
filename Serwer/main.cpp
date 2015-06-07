#include "Header.h"
#include "Ball.h"
#include "Team.h"

struct dane_dla_watku // tablica zawiera dane, ktore otrzymaja w¹tki
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

int lenc;
char buf[80];
int i;

int order = 0;
struct Point coefficients[4];

char* team;
char* tempString;

Team* redTeam;
Team* blueTeam;

Ball* ball;

volatile int busy = 0;

void sendCoeff(SOCKET sock)
{
	int i = 0;

	for (i = 0; i < PLAYERS_IN_TEAM; i++)
	{
		sprintf(tempString, "%f", redTeam->GetPlayers()[i]->GetX());
		send(sock, tempString, 160, 0);
		sprintf(tempString, "%f", redTeam->GetPlayers()[i]->GetY());
		send(sock, tempString, 160, 0);
	}

	for (i = 0; i < PLAYERS_IN_TEAM; i++)
	{
		sprintf(tempString, "%f", blueTeam->GetPlayers()[i]->GetX());
		send(sock, tempString, 160, 0);
		sprintf(tempString, "%f", blueTeam->GetPlayers()[i]->GetY());
		send(sock, tempString, 160, 0);
	}
}

DWORD WINAPI connection(void *argumenty)
{
	struct dane_dla_watku *moje_dane = (struct dane_dla_watku *)argumenty;
	SOCKET sock = moje_dane->s;
	int number = moje_dane->numer;

	while (recv(sock, buf, 80, 0) > 0)
	{
		
		if (strcmp(buf, "Initialize") == 0)
		{
			while (busy == 1);
			busy = 1;

			order++;
			printf("Hey! %d player(s) already!\n", order);
			sprintf(tempString, "%d", order); //ile zawodnikow zrobilem juz przed Toba lacznie z Toba

			send(sock, tempString, 80, 0);
			if (order <= PLAYERS_IN_TEAM)
				team = "red";
			else
				team = "blue";
			send(sock, team, 80, 0);
			
			if (order == PLAYERS_IN_TEAM * 2)
				printf("All players joined server.\n");
			busy = 0;
		}
		else if (strcmp(buf, "Check") == 0)
		{
			while (busy == 1);
			busy = 1;

			printf("Gracz %d sprawdza, czy sa wszyscy gracze.\n", number);
			sprintf(tempString, "%d", order); //ile zawodnikow zrobilem juz przed Toba lacznie z Toba

			send(sock, tempString, 80, 0);

			if (order == PLAYERS_IN_TEAM * 2)
				sendCoeff(sock);
			printf("Gracz %d koncz sprawdzac.\n", number);

			busy = 0;
		}
		else if (strcmp(buf, "GetCoeff") == 0)
		{
			while (busy == 1);
			busy = 1;

			printf("Gracz %d pobiera dane.\n", number);
			sendCoeff(sock);
			printf("Gracz %d konczy pobierac dane.\n", number);

			busy = 0;
		}
		else if (strcmp(buf, "Move") == 0)
		{
			while (busy == 1);
			busy = 1;

			printf("Gracz %d rusza sie.\n", number);
			recv(sock, buf, 80, 0);
			int current = atoi(buf);
			current--;
			recv(sock, buf, 80, 0);

			double change = 0.25;
			double deltaMove = 5;
			if (strcmp(buf, "Up") == 0)
			{
				if (current < PLAYERS_IN_TEAM)
				{
					for (double i = 0; i < deltaMove; i += change)
						redTeam->GetPlayers()[current]->AddY(-change);
				}

				else
				{
					for (double i = 0; i < deltaMove; i += change)
						blueTeam->GetPlayers()[current - PLAYERS_IN_TEAM]->AddY(-change);
				}
				sendCoeff(sock);
			}
			if (strcmp(buf, "Down") == 0)
			{
				if (current < PLAYERS_IN_TEAM)
				{
					for (double i = 0; i < deltaMove; i += change)
						redTeam->GetPlayers()[current]->AddY(change);
				}

				else
				{
					for (double i = 0; i < deltaMove; i += change)
						blueTeam->GetPlayers()[current - PLAYERS_IN_TEAM]->AddY(change);
				}
				sendCoeff(sock);
			}
			if (strcmp(buf, "Left") == 0)
			{
				if (current < PLAYERS_IN_TEAM)
				{
					for (double i = 0; i < deltaMove; i += change)
						redTeam->GetPlayers()[current]->AddX(-change);
				}

				else
				{
					for (double i = 0; i < deltaMove; i += change)
						blueTeam->GetPlayers()[current - PLAYERS_IN_TEAM]->AddX(-change);
				}
				sendCoeff(sock);
			}
			if (strcmp(buf, "Right") == 0)
			{
				if (current < PLAYERS_IN_TEAM)
				{
					for (double i = 0; i < deltaMove; i += change)
						redTeam->GetPlayers()[current]->AddX(change);
				}

				else
				{
					for (double i = 0; i < deltaMove; i += change)
						blueTeam->GetPlayers()[current - PLAYERS_IN_TEAM]->AddX(change);
				}
				sendCoeff(sock);
			}
			printf("Gracz %d konczy ruch.\n", number);

			busy = 0;
		}
		else if (strcmp(buf, "End") == 0)
		{
			while (busy == 1);
			busy = 1;

			printf("One out.\n");
			busy = 0;
			closesocket(sock);
			WSACleanup();
			return 0;
		}	
	}
	printf("One out.\n");
	closesocket(sock);
	WSACleanup();
	return 0;
}


int main()
{
	team = (char*)malloc(sizeof(char) * (PLAYERS_IN_TEAM * 2));
	tempString = (char*)malloc(sizeof(char) * 160);

	redTeam = new Team(red);
	blueTeam = new Team(blue);

	ball = new Ball(490, 245 + (WINDOW_HEIGHT - COURT_HEIGHT));

	wersja = MAKEWORD(1, 1);
	result = WSAStartup(wersja, &wsas);

	s = socket(AF_INET, SOCK_STREAM, 0);


	memset((void *)(&sa), 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(3000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	result = bind(s, (struct sockaddr FAR*)&sa, sizeof(sa));

	result = listen(s, PLAYERS_IN_TEAM * 2 + 1);

	
	while (1)
	{
		SOCKET so = SOCKET_ERROR;

		while (so == SOCKET_ERROR)
		{
			lenc = sizeof(sc);
			so = accept(s, (struct sockaddr FAR *) &sc, &lenc);
		}
			
			DWORD dwThreadId;
			dane[order].numer = order;
			dane[order].s = so;
			HANDLE h = CreateThread(
				NULL, // atrybuty bezpieczeñstwa
				0, // inicjalna wielkoœæ stosu
				connection, // funkcja w¹tku
				(void *)&dane[order],// dane dla funkcji w¹tku
				0, // flagi utworzenia
				&dwThreadId);
		}

	return 0;
}