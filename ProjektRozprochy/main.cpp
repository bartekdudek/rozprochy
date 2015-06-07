#include "Header.h"
#include "Team.h"
#include "Ball.h"
#include <winsock.h>

enum Direction
{
	left,
	right,
	up,
	down
};

void receiveCoeffs(SOCKET s, Point* allCoefficients, Team* redTeam, Team* blueTeam)
{
	int i;
	char* tmp = (char*)malloc(sizeof(char) * 160);

	for (i = 0; i < PLAYERS_IN_TEAM; i++)
	{
		recv(s, tmp, 160, 0);
		redTeam->GetPlayers()[i]->SetX(atof(tmp));
		recv(s, tmp, 160, 0);
		redTeam->GetPlayers()[i]->SetY(atof(tmp));
	}

	for (i = 0; i < PLAYERS_IN_TEAM; i++)
	{
		recv(s, tmp, 160, 0);
		blueTeam->GetPlayers()[i]->SetX(atof(tmp));
		recv(s, tmp, 160, 0);
		blueTeam->GetPlayers()[i]->SetY(atof(tmp));
	}
}

int main()
{
	SOCKET s;
	struct sockaddr_in sa;
	WSADATA wsas;
	WORD wersja;
	int result;

	int i;

	srand(time(NULL));
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY* window;

	ALLEGRO_MOUSE_STATE mouse; 
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT event;

	ALLEGRO_BITMAP* court;
	ALLEGRO_FONT *font;
	
	bool run;
	int busy = 0;

	run = true;
	window = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	al_set_window_title(window, "HaxBall");

	ALLEGRO_TIMER* mainTimer = al_create_timer(1.0 / FPS);
	ALLEGRO_TIMER* loadingTimer = al_create_timer(1.0 / 20.0);

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(mainTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(loadingTimer));
	al_register_event_source(event_queue, al_get_display_event_source(window));

	court = al_load_bitmap("court.png");
	font = al_load_ttf_font("Dolce_Vita.ttf", 72, 30);

	Team* redTeam = new Team(red);
	Team* blueTeam = new Team(blue);

	Ball* ball = new Ball(490, 245 + (WINDOW_HEIGHT - COURT_HEIGHT));

	bool direction[4] = { false, false, false, false };

	Point allCoefficients[PLAYERS_IN_TEAM * 2];

	int order;
	Squad team;

	wersja = MAKEWORD(2, 0);
	WSAStartup(wersja, &wsas);
	s = socket(AF_INET, SOCK_STREAM, 0);
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 160;

	memset((void *)(&sa), 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(3000);
	sa.sin_addr.s_addr = inet_addr("127.0.0.1"); //testowe
	//sa.sin_addr.s_addr = inet_addr("192.168.1.102");


	result = connect(s, (struct sockaddr FAR *) &sa, sizeof(sa));
	if (result == SOCKET_ERROR)
	{
		al_clear_to_color(al_map_rgb(204, 153, 255));
		al_draw_text(font, al_map_rgb(255, 0, 0), 0, 20, 0, "No connection!");
		al_flip_display();
	}
	
	char* tmp = (char*)malloc(sizeof(char) * 80);

	send(s, "Initialize", 80, 0);
	recv(s, tmp, 80, 0);
	order = atoi(tmp);

	recv(s, tmp, 80, 0);

	if (strcmp(tmp, "red") == 0)
		team = red;
	else
		team = blue;

	bool ok = false;


	al_start_timer(mainTimer);
	al_start_timer(loadingTimer);
	while (run == true)
	{
		
		al_wait_for_event(event_queue, &event);
		al_get_mouse_state(&mouse);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			send(s, "End", 80, 0);
			run = false;
		}

		if (ok != true)
		{
			if (event.type == ALLEGRO_EVENT_TIMER)
			{
				while (busy == 1);
				busy = 1;
				send(s, "Check", 80, 0);
				recv(s, tmp, 80, 0);

				int a = atoi(tmp);
				if (a == PLAYERS_IN_TEAM * 2)
				{
					ok = true;

					receiveCoeffs(s, allCoefficients, redTeam, blueTeam);
				}
				else
				{
					ok = false;
					al_clear_to_color(al_map_rgb(204, 153, 255));
					al_draw_text(font, al_map_rgb(255, 0, 0), 0, 20, 0, "Waiting for other players...");
					al_flip_display();
				}
				busy = 0;
				continue;
			}
			
		}
		else
		{
			double change = 0.25;
			double deltaMove = 3;


				if (event.type == ALLEGRO_EVENT_TIMER)
				{
					while (busy == 1);
					busy = 1;
					if (direction[up] == true)
					{
						send(s, "Move", 80, 0);
						sprintf(tmp, "%d", order);
						send(s, tmp, 80, 0);
						send(s, "Up", 80, 0);
						receiveCoeffs(s, allCoefficients, redTeam, blueTeam);
					}
					if (direction[down] == true)
					{
						send(s, "Move", 80, 0);
						sprintf(tmp, "%d", order);
						send(s, tmp, 80, 0);
						send(s, "Down", 80, 0);
						receiveCoeffs(s, allCoefficients, redTeam, blueTeam);
					}
					if (direction[left] == true)
					{
						send(s, "Move", 80, 0);
						sprintf(tmp, "%d", order);
						send(s, tmp, 80, 0);
						send(s, "Left", 80, 0);
						receiveCoeffs(s, allCoefficients, redTeam, blueTeam);
					}
					if (direction[right] == true)
					{
						send(s, "Move", 80, 0);
						sprintf(tmp, "%d", order);
						send(s, tmp, 80, 0);
						send(s, "Right", 80, 0);
						receiveCoeffs(s, allCoefficients, redTeam, blueTeam);
					}
					busy = 0;
				}
				if (event.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					while (busy == 1);
					busy = 1;
					switch (event.keyboard.keycode)
					{
					case ALLEGRO_KEY_ESCAPE:
						send(s, "End", 80, 0);
						run = false;
						break;
					case ALLEGRO_KEY_UP:
						direction[up] = true;
						break;
					case ALLEGRO_KEY_DOWN:
						direction[down] = true;
						break;
					case ALLEGRO_KEY_LEFT:
						direction[left] = true;
						break;
					case ALLEGRO_KEY_RIGHT:
						direction[right] = true;
						break;
					}
					busy = 0;
				}
				if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				{
					send(s, "End", 80, 0);
					run = false;
				}
				if (event.type == ALLEGRO_EVENT_KEY_UP)
				{
					switch (event.keyboard.keycode)
					{
					case ALLEGRO_KEY_UP:
						direction[up] = false;
						break;
					case ALLEGRO_KEY_DOWN:
						direction[down] = false;
						break;
					case ALLEGRO_KEY_LEFT:
						direction[left] = false;
						break;
					case ALLEGRO_KEY_RIGHT:
						direction[right] = false;
						break;
					}
				}

				if (event.timer.source == loadingTimer)
				{
					while (busy == 1);
					busy = 1;
					send(s, "GetCoeff", 80, 0);
					receiveCoeffs(s, allCoefficients, redTeam, blueTeam);
					busy = 0;
				}
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

	al_destroy_event_queue(event_queue);
	al_destroy_timer(mainTimer);
	al_destroy_timer(loadingTimer);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_destroy_display(window);
	al_destroy_font(font);

	return 0;
}