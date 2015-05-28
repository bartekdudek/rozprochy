#include "Header.h"
#include "Team.h"
#include "Ball.h"

enum Direction
{
	left,
	right,
	up,
	down
};

int main()
{
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

	run = true;
	window = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	al_set_window_title(window, "HaxBall");

	ALLEGRO_TIMER* mainTimer = al_create_timer(1.0 / FPS);

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(mainTimer));
	al_register_event_source(event_queue, al_get_display_event_source(window));

	court = al_load_bitmap("court.png");
	font = al_load_ttf_font("Dolce_Vita.ttf", 72, 10);

	Team* redTeam = new Team(red);
	Team* blueTeam = new Team(blue);

	Ball* ball = new Ball(490, 245 + (WINDOW_HEIGHT - COURT_HEIGHT));

	bool direction[4] = { false, false, false, false };

	al_start_timer(mainTimer);
	while (run == true)
	{
		al_wait_for_event(event_queue, &event);
		al_get_mouse_state(&mouse);

		double change = 0.25;
		double deltaMove = 3;
		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			if (direction[up] == true)
			{
				for (double i = 0; i < deltaMove; i += change)
					redTeam->GetPlayers()[0]->AddY(-change);
			}
			if (direction[down] == true)
			{
				for (double i = 0; i < deltaMove; i += change)
					redTeam->GetPlayers()[0]->AddY(change);
			}
			if (direction[left] == true)
			{
				for (double i = 0; i < deltaMove; i += change)
					redTeam->GetPlayers()[0]->AddX(-change);
			}
			if (direction[right] == true)
			{
				for (double i = 0; i < deltaMove; i += change)
					redTeam->GetPlayers()[0]->AddX(change);
			}
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
				case ALLEGRO_KEY_ESCAPE:
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
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
		{
			run = false;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
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

	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_destroy_display(window);
	al_destroy_font(font);

	return 0;
}