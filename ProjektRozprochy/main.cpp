#include "Main.h"

void receiveCoeffs(SOCKET s, Image** images)
{
	int i;
	char tmp[STRING_SIZE];

	for (i = 0; i < (numberOfPlayersInTeam*2 + 1); i++)
	{
		recv(s, tmp, STRING_SIZE, 0);
		images[i]->setX(atof(tmp));
		recv(s, tmp, STRING_SIZE, 0);
		images[i]->setY(atof(tmp));
	}

	recv(s, tmp, STRING_SIZE, 0);
	redScore = atoi(tmp);
	recv(s, tmp, STRING_SIZE, 0);
	blueScore = atoi(tmp);
}

int main()
{
	ALLEGRO_DISPLAY* window;

	ALLEGRO_MOUSE_STATE mouse;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_EVENT event;

	ALLEGRO_BITMAP* court;
	ALLEGRO_FONT *font;

	ALLEGRO_TIMER* mainTimer;
	ALLEGRO_TIMER* loadingTimer;

	bool run;
	bool ok;
	bool over;

	char tmp[STRING_SIZE];

	int order;
	Squad team;

	HANDLE ghMutex;

	SOCKET s;
	struct sockaddr_in sa;
	WSADATA wsas;
	WORD wersja;
	int result;

	Image** images;

	int i, j;

	char redScoreString[10];
	char blueScoreString[10];

	char winningTeam[10];

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
	over = false;

	window = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	al_set_window_title(window, "HaxBall");

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(mainTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(loadingTimer));
	al_register_event_source(event_queue, al_get_display_event_source(window));

	court = al_load_bitmap("Resources/court.png");
	font = al_load_ttf_font("Resources/Dolce_Vita.ttf", 72, 30);


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
	numberOfPlayersInTeam = atoi(tmp);

	recv(s, tmp, STRING_SIZE, 0);
	order = atoi(tmp);

	recv(s, tmp, STRING_SIZE, 0);

	if (strcmp(tmp, "red") == 0)
		team = red;
	else
		team = blue;

	
	images = new Image*[numberOfPlayersInTeam * 2 + 1];

	j = 0;
	for (i = 0; i < numberOfPlayersInTeam; i++, j++)
		images[j] = new Image(redPlayer, PLAYER_SIZE);
	for (i = 0; i < numberOfPlayersInTeam; i++, j++)
		images[j] = new Image(bluePlayer, PLAYER_SIZE);

	images[j] = new Image(ball, BALL_SIZE);



	al_start_timer(mainTimer);
	al_start_timer(loadingTimer);

	while (run == true)
	{
		
		al_wait_for_event(event_queue, &event);
		al_get_mouse_state(&mouse);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			WaitForSingleObject(ghMutex, INFINITE);

			send(s, "End", STRING_SIZE, 0);

			ReleaseMutex(ghMutex);
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
				if (a == numberOfPlayersInTeam * 2)
				{
					ok = true;
					receiveCoeffs(s, images);
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
			if (event.type == ALLEGRO_EVENT_KEY_DOWN && over == false)
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
				case ALLEGRO_KEY_SPACE:
					WaitForSingleObject(ghMutex, INFINITE);

					send(s, "Kick", STRING_SIZE, 0);

					ReleaseMutex(ghMutex);
					break;
				}
			}
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				send(s, "End", STRING_SIZE, 0);

				ReleaseMutex(ghMutex);

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

			if (event.timer.source == loadingTimer && over == false)
			{
				WaitForSingleObject(ghMutex, INFINITE);

				send(s, "GetCoeff", STRING_SIZE, 0);
				recv(s, tmp, STRING_SIZE, 0);
				if (strcmp(tmp, "GAMEOVER") == 0)
				{
					recv(s, tmp, STRING_SIZE, 0);
					strcpy(winningTeam, tmp);
					over = true;
				}
				else
				{
					receiveCoeffs(s, images);
				}
				ReleaseMutex(ghMutex);
			}
			else if (event.timer.source == mainTimer)
			{
				al_clear_to_color(al_map_rgb(204, 153, 255));

				sprintf(redScoreString, "%d", redScore);
				sprintf(blueScoreString, "%d", blueScore);

				al_draw_text(font, al_map_rgb(255, 0, 0), WINDOW_WIDTH / 2 - 70, 20, 0, redScoreString);
				al_draw_text(font, al_map_rgb(0, 0, 0), WINDOW_WIDTH / 2, 20, 0, ":");
				al_draw_text(font, al_map_rgb(0, 0, 255), WINDOW_WIDTH / 2 + 50, 20, 0, blueScoreString);

				al_draw_bitmap(court, 0, WINDOW_HEIGHT - 486, 0);

				for (i = 0; i < (numberOfPlayersInTeam * 2 + 1); i++)
					images[i]->Draw();

				if (over == true)
				{
					if (strcmp(winningTeam, "red") == 0)
						al_draw_text(font, al_map_rgb(0, 0, 0), WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2, 0, "Red team wins!");
					else if (strcmp(winningTeam, "blue") == 0)
						al_draw_text(font, al_map_rgb(0, 0, 0), WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2, 0, "Blue team wins!");
				}

				al_flip_display();
			}
		}
	}

	CloseHandle(ghMutex);

	delete[] images;

	al_destroy_event_queue(event_queue);
	al_destroy_timer(mainTimer);
	al_destroy_timer(loadingTimer);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_destroy_display(window);
	al_destroy_font(font);

	return 0;
}