#include "Main.h"

void sendCoeff(SOCKET sock)
{
	int i = 0;
	char tempString[STRING_SIZE];

	for (i = 0; i < PLAYERS_IN_TEAM; i++)
	{
		sprintf(tempString, "%f", redTeam->GetPlayers()[i]->GetX());
		send(sock, tempString, STRING_SIZE, 0);
		sprintf(tempString, "%f", redTeam->GetPlayers()[i]->GetY());
		send(sock, tempString, STRING_SIZE, 0);
	}

	for (i = 0; i < PLAYERS_IN_TEAM; i++)
	{
		sprintf(tempString, "%f", blueTeam->GetPlayers()[i]->GetX());
		send(sock, tempString, STRING_SIZE, 0);
		sprintf(tempString, "%f", blueTeam->GetPlayers()[i]->GetY());
		send(sock, tempString, STRING_SIZE, 0);
	}

	sprintf(tempString, "%f", ball->getX());
	send(sock, tempString, STRING_SIZE, 0);
	sprintf(tempString, "%f", ball->getY());
	send(sock, tempString, STRING_SIZE, 0);

	sprintf(tempString, "%f", redTeam->GetScore());
	send(sock, tempString, STRING_SIZE, 0);
	sprintf(tempString, "%f", blueTeam->GetScore());
	send(sock, tempString, STRING_SIZE, 0);

}

void movePlayers(int number, int direction[4])
{
	if (direction[up] == 1)
	{
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
	}
	if (direction[down] == 1)
	{
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
	}
	if (direction[left] == 1)
	{
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
	}
	if (direction[right] == 1)
	{
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
	}
}

DWORD WINAPI connection(void *argumenty)
{
	char buf[STRING_SIZE];
	char tempString[STRING_SIZE];
	char team[STRING_SIZE];

	struct dane_dla_watku *moje_dane = (struct dane_dla_watku *)argumenty;
	SOCKET sock = moje_dane->s;
	int number = moje_dane->numer;
	int direction[4] = { 0, 0, 0, 0 };

	while (1)
	{
		if (recv(sock, buf, STRING_SIZE, 0) > 0)
		{
			if (strcmp(buf, "Initialize") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);
				sprintf(tempString, "%d", PLAYERS_IN_TEAM);
				send(sock, tempString, STRING_SIZE, 0);
				order++;
				printf("Hey! %d player(s) already!\n", order);
				sprintf(tempString, "%d", order);

				send(sock, tempString, STRING_SIZE, 0);
				if (order <= PLAYERS_IN_TEAM)
					strcpy(team, "red");
				else
					strcpy(team, "blue");

				send(sock, team, STRING_SIZE, 0);

				if (order == PLAYERS_IN_TEAM * 2)
					printf("All players joined server.\n");

				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "Check") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				sprintf(tempString, "%d", order);

				send(sock, tempString, STRING_SIZE, 0);

				if (order == PLAYERS_IN_TEAM * 2)
					sendCoeff(sock);

				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "GetCoeff") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				sendCoeff(sock);

				ReleaseMutex(ghMutex);
			}

			else if (strcmp(buf, "UpTrue") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				direction[up] = 1;

				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "DownTrue") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				direction[down] = 1;

				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "LeftTrue") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				direction[left] = 1;

				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "RightTrue") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				direction[right] = 1;

				ReleaseMutex(ghMutex);
			}

			else if (strcmp(buf, "UpFalse") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				direction[up] = 0;
				
				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "DownFalse") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				direction[down] = 0;

				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "LeftFalse") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				direction[left] = 0;

				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "RightFalse") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				direction[right] = 0;

				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "End") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);
				
				closesocket(sock);
				WSACleanup();

				ReleaseMutex(ghMutex);
				return 0;
			}

			WaitForSingleObject(ghMutex, INFINITE);

			movePlayers(number, direction);

			ReleaseMutex(ghMutex);
		}
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}


int main()
{
	srand(time(NULL));
	ghMutex = CreateMutex(NULL, FALSE, NULL);

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

	delete ball;
	delete blueTeam;
	delete redTeam;

	return 0;
}