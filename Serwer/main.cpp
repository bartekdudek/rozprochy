#include "Main.h"

double fsign(double v)
{
	if (v < 0)
	{
		return MINUS_ONE;
	}
	else
	{
		return PLUS_ONE;
	}

}

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

	sprintf(tempString, "%f", ball->GetX());
	send(sock, tempString, STRING_SIZE, 0);
	sprintf(tempString, "%f", ball->GetY());
	send(sock, tempString, STRING_SIZE, 0);
}

void movePlayers(int number, int direction[4], int& kick)
{
	if (kick == 0)
	{
		if (direction[up] == 1)
		{
			if (number < PLAYERS_IN_TEAM)
			{
				for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
					redTeam->GetPlayers()[number]->AddY(-MOVE_CHANGE, redTeam, blueTeam, ball);
			}

			else
			{
				for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
					blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->AddY(-MOVE_CHANGE, redTeam, blueTeam, ball);
			}
		}
		if (direction[down] == 1)
		{
			if (number < PLAYERS_IN_TEAM)
			{
				for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
					redTeam->GetPlayers()[number]->AddY(MOVE_CHANGE, redTeam, blueTeam, ball);
			}

			else
			{
				for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
					blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->AddY(MOVE_CHANGE, redTeam, blueTeam, ball);
			}
		}
		if (direction[left] == 1)
		{
			if (number < PLAYERS_IN_TEAM)
			{
				for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
					redTeam->GetPlayers()[number]->AddX(-MOVE_CHANGE, redTeam, blueTeam, ball);
			}

			else
			{
				for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
					blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->AddX(-MOVE_CHANGE, redTeam, blueTeam, ball);
			}
		}
		if (direction[right] == 1)
		{
			if (number < PLAYERS_IN_TEAM)
			{
				for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
					redTeam->GetPlayers()[number]->AddX(MOVE_CHANGE, redTeam, blueTeam, ball);
			}

			else
			{
				for (double i = 0; i < MOVE_DELTA; i += MOVE_CHANGE)
					blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->AddX(MOVE_CHANGE, redTeam, blueTeam, ball);
			}
		}
	}

	kick = 0;
	ball->MoveBall(redTeam, blueTeam, &redScore, &blueScore);
}

DWORD WINAPI connection(void *argumenty)
{
	char buf[STRING_SIZE];
	char tempString[STRING_SIZE];
	char team[STRING_SIZE];

	int kick;

	struct dane_dla_watku *moje_dane = (struct dane_dla_watku *)argumenty;
	SOCKET sock = moje_dane->s;
	int number = moje_dane->numer;
	int direction[4] = { 0, 0, 0, 0 };

	kick = 0;

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

				if (redScore >= WINNING_SCORE)
				{
					over = true;
					strcpy(winningTeam, "red");
				}

				else if (blueScore >= WINNING_SCORE)
				{
					over = true;
					strcpy(winningTeam, "blue");
				}

				sprintf(tempString, "%d", redScore);
				send(sock, tempString, STRING_SIZE, 0);
				sprintf(tempString, "%d", blueScore);
				send(sock, tempString, STRING_SIZE, 0);



				if (over == true)
				{
					send(sock, "GAMEOVER", STRING_SIZE, 0);
					strcpy(tempString, winningTeam);
					send(sock, tempString, STRING_SIZE, 0);
				}

				else
				{
					send(sock, "GAMENOTOVER", STRING_SIZE, 0);
					sendCoeff(sock);
				}

				ReleaseMutex(ghMutex);
			}

			else if (strcmp(buf, "UpTrue") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				direction[up] = 1;
				if (number < PLAYERS_IN_TEAM)
				{
					redTeam->GetPlayers()[number]->SetHorizontally(true, -1.0);
				}

				else
				{
					blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->SetHorizontally(true, -1.0);
				}
				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "DownTrue") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				direction[down] = 1;
				if (number < PLAYERS_IN_TEAM)
				{
					redTeam->GetPlayers()[number]->SetHorizontally(true, 1.0);
				}

				else
				{
					blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->SetHorizontally(true, 1.0);
				}
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

				if (number < PLAYERS_IN_TEAM)
				{
					redTeam->GetPlayers()[number]->SetHorizontally(false, NULL);
				}

				else
				{
					blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->SetHorizontally(false, NULL);
				}
				
				ReleaseMutex(ghMutex);
			}
			else if (strcmp(buf, "DownFalse") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				direction[down] = 0;

				if (number < PLAYERS_IN_TEAM)
				{
					redTeam->GetPlayers()[number]->SetHorizontally(false, NULL);
				}

				else
				{
					blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->SetHorizontally(false, NULL);
				}

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

				over = true;
				if (number < PLAYERS_IN_TEAM)
					strcpy(winningTeam, "blue");
				else
					strcpy(winningTeam, "red");
				
				closesocket(sock);

				ReleaseMutex(ghMutex);
				return 0;
			}
			else if (strcmp(buf, "Kick") == 0)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				if (number < PLAYERS_IN_TEAM)
				{
					redTeam->GetPlayers()[number]->Kicked(ball);
				}

				else
				{
					blueTeam->GetPlayers()[number - PLAYERS_IN_TEAM]->Kicked(ball);
				}

				kick = 1;

				ReleaseMutex(ghMutex);
			}

			WaitForSingleObject(ghMutex, INFINITE);

			movePlayers(number, direction, kick);

			ReleaseMutex(ghMutex);
		}
	}
	closesocket(sock);
	return 0;
}


int main()
{
	srand(time(NULL));
	ghMutex = CreateMutex(NULL, FALSE, NULL);

	redTeam = new Team(red);
	blueTeam = new Team(blue);

	ball = new Ball(491, 245 + (WINDOW_HEIGHT - COURT_HEIGHT));

	wersja = MAKEWORD(1, 1);
	result = WSAStartup(wersja, &wsas);

	s = socket(AF_INET, SOCK_STREAM, 0);


	memset((void *)(&sa), 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	result = bind(s, (struct sockaddr FAR*)&sa, sizeof(sa));

	result = listen(s, PLAYERS_IN_TEAM * 2 + 1);


	while (1)
	{
		lenc = sizeof(sc);
		si[order] = accept(s, (struct sockaddr FAR *) &scomplete[order], &lenc);

		DWORD dwThreadId;
		dane[order].numer = order;
		dane[order].s = si[order];
		HANDLE h = CreateThread(NULL, 0, connection, (void *)&dane[order], 0, &dwThreadId);
	}

	CloseHandle(ghMutex);

	delete ball;
	delete blueTeam;
	delete redTeam;

	WSACleanup();

	return 0;
}