#include<stdio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>

int main() {

	al_init_primitives_addon();
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* queue = NULL;
	ALLEGRO_TIMER* timer;

	al_init();
	al_install_keyboard();

	display = al_create_display(600, 600);
	timer = al_create_timer(1.0 / 20); // saniyede gönderme hızı
	queue = al_create_event_queue();
	al_start_timer(timer);

	int layerXPos = 280, layerYPos = 550; // for layer
	int ballXPos = 310, ballYPos = 540; // for ball
	int direction = 1; // for ball's move

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(queue, &ev);

		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT && layerXPos < 525)
		{
			layerXPos += 10;
		}
		else if (ev.keyboard.keycode==ALLEGRO_KEY_LEFT && layerXPos>20)
		{
			layerXPos -= 10;
		}

		if (abs(ballYPos-layerYPos)<=10)
		{
			direction = 1;
		}
		else if (abs(ballXPos-600)<=10)
		{
			direction = 2;
		}
		else if (ballYPos<=10)
		{
			direction = 3;
		}
		else if (ballXPos<=10)
		{
			direction = 4;
		}

		if (direction==1)
		{
			ballXPos += 3;
			ballYPos -= 3;
		}
		else if (direction==2)
		{
			ballXPos -= 3;
			ballYPos -= 3;
		}
		else if (direction==3)
		{
			ballXPos -= 3;
			ballYPos += 3;
		}
		else if(direction==4)
		{
			ballXPos += 3;
			ballYPos += 3;
		}

		al_draw_filled_rectangle(layerXPos, layerYPos, layerXPos + 60, layerYPos + 10, al_map_rgb(255, 255, 255));
		al_draw_filled_circle(ballXPos, ballYPos, 10, al_map_rgb(255, 255, 255));
		al_flip_display();
	}

	system("pause");
	al_destroy_display(display);
	al_destroy_event_queue(queue);

	return 0;
}