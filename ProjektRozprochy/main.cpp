#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

int main()
{
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();

	ALLEGRO_DISPLAY* window;

	ALLEGRO_MOUSE_STATE mouse; 
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT event;
	
	bool run;

	run = true;
	window = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	al_set_window_title(window, "HaxBall");

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(window));

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

	}

	al_destroy_event_queue(event_queue);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_destroy_display(window);


	return 0;
}