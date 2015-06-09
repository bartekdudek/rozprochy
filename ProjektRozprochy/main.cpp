#include "Header.h"
#include "Team.h"
#include "Ball.h"
#include <winsock.h>


void receiveCoeffs(SOCKET s, Team* redTeam, Team* blueTeam)
{
	int i;
	char tmp[STRING_SIZE];

	if (tmp)
	{
		for (i = 0; i < PLAYERS_IN_TEAM; i++)
		{
			recv(s, tmp, STRING_SIZE, 0);
			redTeam->GetPlayers()[i]->SetX(atof(tmp));
			recv(s, tmp, STRING_SIZE, 0);
			redTeam->GetPlayers()[i]->SetY(atof(tmp));
		}

		for (i = 0; i < PLAYERS_IN_TEAM; i++)
		{
			recv(s, tmp, STRING_SIZE, 0);
			blueTeam->GetPlayers()[i]->SetX(atof(tmp));
			recv(s, tmp, STRING_SIZE, 0);
			blueTeam->GetPlayers()[i]->SetY(atof(tmp));
		}
	}
}

int main()
{
	ALLEGRO_DISPLAY* window;

	ALLEGRO_MOUSE_STATE mouse;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT event;

	ALLEGRO_BITMAP* court;
	ALLEGRO_FONT *font;

	ALLEGRO_TIMER* mainTimer;
	ALLEGRO_TIMER* loadingTimer;

	bool run;
	bool ok;

	char tmp[STRING_SIZE];

	Team* redTeam;
	Team* blueTeam;
	Ball* ball;

	int order;
	Squad team;

	HANDLE ghMutex;

	SOCKET s;
	struct sockaddr_in sa;
	WSADATA wsas;
	WORD wersja;
	int result;


	srand(time(NULL));
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	mainTimer = al_create_timer(1.0 / FPS);
	loadingTimer = al_create_timer(1.0 / LPS);

	ghMutex = CreateMutex(NULL, FALSE, NULL);

	run = true;
	ok = false;

	window = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	al_set_window_title(window, "HaxBall");

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(mainTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(loadingTimer));
	al_register_event_source(event_queue, al_get_display_event_source(window));

	court = al_load_bitmap("court.png");
	font = al_load_ttf_font("Dolce_Vita.ttf", 72, 30);

	redTeam = new Team(red);
	blueTeam = new Team(blue);
	ball = new Ball(490, 245 + (WINDOW_HEIGHT - COURT_HEIGHT));

	wersja = MAKEWORD(2, 0);
	WSAStartup(wersja, &wsas);
	s = socket(AF_INET, SOCK_STREAM, 0);

	memset((void *)(&sa), 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = inet_addr("127.0.0.1"); //testowe
	//sa.sin_addr.s_addr = inet_addr("192.168.1.102");

	result = connect(s, (struct sockaddr FAR *) &sa, sizeof(sa));
	if (result == SOCKET_ERROR)
	{
		al_clear_to_color(al_map_rgb(204, 153, 255));
		al_draw_text(font, al_map_rgb(255, 0, 0), 0, 20, 0, "No connection!");
		al_flip_display();
	}

	send(s, "Initialize", STRING_SIZE, 0);
	recv(s, tmp, STRING_SIZE, 0);
	order = atoi(tmp);

	recv(s, tmp, STRING_SIZE, 0);

	if (strcmp(tmp, "red") == 0)
		team = red;
	else
		team = blue;


	al_start_timer(mainTimer);
	al_start_timer(loadingTimer);

	while (run == true)
	{
		
		al_wait_for_event(event_queue, &event);
		al_get_mouse_state(&mouse);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			send(s, "End", STRING_SIZE, 0);
			run = false;
		}

		if (ok != true)
		{
			if (event.type == ALLEGRO_EVENT_TIMER)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				send(s, "Check", STRING_SIZE, 0);
				recv(s, tmp, STRING_SIZE, 0);

				int a = atoi(tmp);
				if (a == PLAYERS_IN_TEAM * 2)
				{
					ok = true;
					receiveCoeffs(s, redTeam, blueTeam);
				}
				else
				{
					ok = false;
					al_clear_to_color(al_map_rgb(204, 153, 255));
					al_draw_text(font, al_map_rgb(255, 0, 0), 0, 20, 0, "Waiting for other players...");
					al_flip_display();
				}

				ReleaseMutex(ghMutex);
				continue;
			}
			
		}
		else
		{
			if (event.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					WaitForSingleObject(ghMutex, INFINITE);

					send(s, "End", STRING_SIZE, 0);

					ReleaseMutex(ghMutex);
					run = false;
					break;
				case ALLEGRO_KEY_UP:
					WaitForSingleObject(ghMutex, INFINITE);

					send(s, "UpTrue", STRING_SIZE, 0);

					ReleaseMutex(ghMutex);
					break;
				case ALLEGRO_KEY_DOWN:
					WaitForSingleObject(ghMutex, INFINITE);

					send(s, "DownTrue", STRING_SIZE, 0);

					ReleaseMutex(ghMutex);
					break;
				case ALLEGRO_KEY_LEFT:
					WaitForSingleObject(ghMutex, INFINITE);

					send(s, "LeftTrue", STRING_SIZE, 0);

					ReleaseMutex(ghMutex);
					break;
				case ALLEGRO_KEY_RIGHT:
					WaitForSingleObject(ghMutex, INFINITE);

					send(s, "RightTrue", STRING_SIZE, 0);

					ReleaseMutex(ghMutex);
					break;
				}
			}
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				send(s, "End", STRING_SIZE, 0);
				run = false;
			}
			if (event.type == ALLEGRO_EVENT_KEY_UP)
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_UP:
					WaitForSingleObject(ghMutex, INFINITE);

					send(s, "UpFalse", STRING_SIZE, 0);

					ReleaseMutex(ghMutex);
					break;
				case ALLEGRO_KEY_DOWN:
					WaitForSingleObject(ghMutex, INFINITE);

					send(s, "DownFalse", STRING_SIZE, 0);

					ReleaseMutex(ghMutex);
					break;
				case ALLEGRO_KEY_LEFT:
					WaitForSingleObject(ghMutex, INFINITE);

					send(s, "LeftFalse", STRING_SIZE, 0);

					ReleaseMutex(ghMutex);
					break;
				case ALLEGRO_KEY_RIGHT:
					WaitForSingleObject(ghMutex, INFINITE);

					send(s, "RightFalse", STRING_SIZE, 0);

					ReleaseMutex(ghMutex);
					break;
				}
			}

			if (event.timer.source == loadingTimer)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				send(s, "GetCoeff", STRING_SIZE, 0);
				receiveCoeffs(s, redTeam, blueTeam);

				ReleaseMutex(ghMutex);
			}
			else if (event.timer.source == mainTimer)
			{
				al_clear_to_color(al_map_rgb(204, 153, 255));

				char *redScore = new char[10];
				sprintf(redScore, "%d", redTeam->GetScore());

				char *blueScore = new char[10];
				sprintf(blueScore, "%d", blueTeam->GetScore());

				al_draw_text(font, al_map_rgb(255, 0, 0), WINDOW_WIDTH / 2 - 70, 20, 0, redScore);
				al_draw_text(font, al_map_rgb(0, 0, 0), WINDOW_WIDTH / 2, 20, 0, ":");
				al_draw_text(font, al_map_rgb(0, 0, 255), WINDOW_WIDTH / 2 + 50, 20, 0, blueScore);

				al_draw_bitmap(court, 0, WINDOW_HEIGHT - 486, 0);

				ball->DrawBall();
				redTeam->DrawPlayers();
				blueTeam->DrawPlayers();


				al_flip_display();
			}
		}
	}

	CloseHandle(ghMutex);

	delete ball;
	delete blueTeam;
	delete redTeam;

	al_destroy_event_queue(event_queue);
	al_destroy_timer(mainTimer);
	al_destroy_timer(loadingTimer);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_destroy_display(window);
	al_destroy_font(font);

	return 0;
}