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
int i;

int order = 0;
struct Point coefficients[4];

char* team;
char* tempString;

Team* redTeam;
Team* blueTeam;

Ball* ball;

HANDLE ghMutex;

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
	char buf[80];
	struct dane_dla_watku *moje_dane = (struct dane_dla_watku *)argumenty;
	SOCKET sock = moje_dane->s;
	int number = moje_dane->numer;
	int direction[4] = { 0, 0, 0, 0 };

	while (1)
	{
		if (recv(sock, buf, 80, 0) > 0)
		{
			if (strcmp(buf, "Initialize") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

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
				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "Check") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				printf("Gracz %d sprawdza, czy sa wszyscy gracze.\n", number);
				sprintf(tempString, "%d", order); //ile zawodnikow zrobilem juz przed Toba lacznie z Toba

				send(sock, tempString, 80, 0);

				if (order == PLAYERS_IN_TEAM * 2)
					sendCoeff(sock);
				printf("Gracz %d koncz sprawdzac.\n", number);

				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "GetCoeff") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				printf("Gracz %d pobiera dane.\n", number);
				sendCoeff(sock);
				printf("Gracz %d konczy pobierac dane.\n", number);

				ReleaseMutex(ghMutex);
			}

			else if (strcmp(buf, "UpTrue") == 0)
			{
				direction[up] = 1;
			}
			else if (strcmp(buf, "DownTrue") == 0)
			{
				direction[down] = 1;
			}
			else if (strcmp(buf, "LeftTrue") == 0)
			{
				direction[left] = 1;
			}
			else if (strcmp(buf, "RightTrue") == 0)
			{
				direction[right] = 1;
			}

			else if (strcmp(buf, "UpFalse") == 0)
			{
				direction[up] = 0;
			}
			else if (strcmp(buf, "DownFalse") == 0)
			{
				direction[down] = 0;
			}
			else if (strcmp(buf, "LeftFalse") == 0)
			{
				direction[left] = 0;
			}
			else if (strcmp(buf, "RightFalse") == 0)
			{
				direction[right] = 0;
			}
			else if (strcmp(buf, "End") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				printf("One out.\n");

				ReleaseMutex(ghMutex);
				closesocket(sock);
				WSACleanup();
				return 0;
			}

			if (direction[up] == 1)
			{
				WaitForSingleObject(ghMutex, INFINITE);
				if (number < PLAYERS_IN_TEAM)
				{
					for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
						redTeam->GetPlayers()[number]->AddY(-MOVE_CHANGE);
				}

				else
				{
					for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
						blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->AddY(-MOVE_CHANGE);
				}
				ReleaseMutex(ghMutex);
			}
			if (direction[down] == 1)
			{
				WaitForSingleObject(ghMutex, INFINITE);
				if (number < PLAYERS_IN_TEAM)
				{
					for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
						redTeam->GetPlayers()[number]->AddY(MOVE_CHANGE);
				}

				else
				{
					for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
						blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->AddY(MOVE_CHANGE);
				}
				ReleaseMutex(ghMutex);
			}
			if (direction[left] == 1)
			{
				WaitForSingleObject(ghMutex, INFINITE);
				if (number < PLAYERS_IN_TEAM)
				{
					for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
						redTeam->GetPlayers()[number]->AddX(-MOVE_CHANGE);
				}

				else
				{
					for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
						blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->AddX(-MOVE_CHANGE);
				}
				ReleaseMutex(ghMutex);
			}
			if (direction[right] == 1)
			{
				WaitForSingleObject(ghMutex, INFINITE);
				if (number < PLAYERS_IN_TEAM)
				{
					for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
						redTeam->GetPlayers()[number]->AddX(MOVE_CHANGE);
				}

				else
				{
					for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
						blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->AddX(MOVE_CHANGE);
				}
				ReleaseMutex(ghMutex);
			}
		}
	}
	printf("One out.\n");
	closesocket(sock);
	WSACleanup();
	return 0;
}


int main()
{
	srand(time(NULL));
	ghMutex = CreateMutex(NULL, FALSE, NULL);

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
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	result = bind(s, (struct sockaddr FAR*)&sa, sizeof(sa));

	result = listen(s, PLAYERS_IN_TEAM * 2 + 1);


	while (1)
	{

		lenc = sizeof(sc);
		si[order] = accept(s, (struct sockaddr FAR *) &sc, &lenc);

		DWORD dwThreadId;
		dane[order].numer = order;
		dane[order].s = si[order];
		HANDLE h = CreateThread(NULL, 0, connection, (void *)&dane[order], 0, &dwThreadId);
	}

	CloseHandle(ghMutex);

	return 0;
}