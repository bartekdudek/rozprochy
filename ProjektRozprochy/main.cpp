#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <string>

#define WINDOW_WIDTH 982
#define WINDOW_HEIGHT 600

int main()
{
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

	int redTeamScore = 0;
	int blueTeamScore = 0;

	run = true;
	window = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	al_set_window_title(window, "HaxBall");

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(window));

	court = al_load_bitmap("court.png");
	font = al_load_ttf_font("Dolce_Vita.ttf", 72, 10);

	while (run == true)
	{
		al_wait_for_event(event_queue, &event);
		al_get_mouse_state(&mouse);


		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
				case ALLEGRO_KEY_ESCAPE:
					run = false;
					break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
		{
			run = false;
		}
		al_clear_to_color(al_map_rgb(204, 153, 255));

		char *redScore = new char[10];
		sprintf(redScore, "%d", redTeamScore);

		char *blueScore = new char[10];
		sprintf(blueScore, "%d", blueTeamScore);

		al_draw_text(font, al_map_rgb(255, 0, 0), WINDOW_WIDTH / 2 - 70, 20, 0, redScore);
		al_draw_text(font, al_map_rgb(0, 0, 0), WINDOW_WIDTH / 2, 20, 0, ":");
		al_draw_text(font, al_map_rgb(0, 0, 255), WINDOW_WIDTH / 2 + 50, 20, 0, blueScore);

		al_draw_bitmap(court, 0, WINDOW_HEIGHT - 486, 0);
		al_flip_display();
	}

	al_destroy_event_queue(event_queue);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_destroy_display(window);
	al_destroy_font(font);

	return 0;
}