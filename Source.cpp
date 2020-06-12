#include<stdio.h>
#include<math.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>

int main() {

	al_init_primitives_addon();
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* queue = NULL;
	ALLEGRO_TIMER* timer;

	al_init();
	al_install_keyboard();

	display = al_create_display(600, 700);
	timer = al_create_timer(1.0 / 20); // saniyede gönderme hızı
	queue = al_create_event_queue();
	al_start_timer(timer);

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* font = al_load_font("Merriweather-BoldIt.ttf", 24, 0);

	int layerXPos = 280, layerYPos = 650; // for layer
	int ballXPos = 310, ballYPos = 640; // for ball
	int direction = 1; // for ball's move
	int boxFirstLineX = 0, boxFirstLineY = 50; // first line of boxes begin and end points
	int boxSecondLineX = 0, boxSecondLineY = 111; // second of line of boxes begin and end points
	int exists = 1; // if exists is equal to 1 the ball didn't hit yet else it is equal to 0
	int numberOfBalls = 20;

	int boxes[20][3];

	// defining first box at the first line
	boxes[0][0] = boxFirstLineX;
	boxes[0][1] = boxFirstLineY;
	boxes[0][2] = exists;

	// defining other boxes at the first line
	for (int i = 1; i < 10; i++)
	{
		boxFirstLineX += 61;
		boxes[i][0] = boxFirstLineX;
		boxes[i][1] = boxFirstLineY;
		boxes[i][2] = exists;
	}

	// defining first box at the second line
	boxes[10][0] = boxSecondLineX;
	boxes[10][1] = boxSecondLineY;
	boxes[10][2] = exists;

	// defining other boxes at the second line
	for (int i = 11; i < 20; i++)
	{
		boxSecondLineX += 61;
		boxes[i][0] = boxSecondLineX;
		boxes[i][1] = boxSecondLineY;
		boxes[i][2] = exists;
	}

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(queue, &ev);

		al_clear_to_color(al_map_rgb(0, 0, 0));

		// text

		al_draw_text(font, al_map_rgb(222, 15, 306), 20, 10, 0, "Last");
		al_draw_textf(font, al_map_rgb(222, 15, 306), 70, 10, 0, "%d", numberOfBalls);
		al_draw_text(font, al_map_rgb(222, 15, 306), 120, 10, 0, "Balls");

		// layer

		if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT && layerXPos < 525)
		{
			layerXPos += 10;
		}
		else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT && layerXPos > 20)
		{
			layerXPos -= 10;
		}

		// ball's direction

		if (abs(ballYPos - layerYPos) <= 10)
		{
			direction = 1;
		}
		else if (abs(ballXPos - 600) <= 10)
		{
			direction = 2;
		}
		else if (ballYPos >= 50 && ballYPos <= 60)
		{
			direction = 3;
		}
		else if (ballXPos <= 10)
		{
			direction = 4;
		}

		// balls's movement

		if (direction == 1)
		{
			ballXPos += 3;
			ballYPos -= 3;
		}
		else if (direction == 2)
		{
			ballXPos -= 3;
			ballYPos -= 3;
		}
		else if (direction == 3)
		{
			ballXPos -= 3;
			ballYPos += 3;
		}
		else if (direction == 4)
		{
			ballXPos += 3;
			ballYPos += 3;
		}

		// end of the game

		if ((ballXPos<layerXPos || ballXPos>layerXPos + 60) && ballYPos >= 640)
		{
			system("pause");
		}

		al_draw_filled_rectangle(layerXPos, layerYPos, layerXPos + 60, layerYPos + 10, al_map_rgb(246, 107, 107));
		al_draw_filled_circle(ballXPos, ballYPos, 10, al_map_rgb(240, 204, 204));

		for (int i = 0; i < 20; i++)
		{
			if (boxes[i][2] == 1)
			{
				al_draw_filled_rectangle(boxes[i][0], boxes[i][1], boxes[i][0] + 60, boxes[i][1] + 60, al_map_rgb(210, 47, 140));
			}
		}

		// collision

		float distance = 10 + 30 * sqrt(2);
		for (int i = 0; i < 20; i++)
		{
			if (boxes[i][2] == 1) {
				float box = boxes[i][0] + (30 * sqrt(2));
				if (fabs(ballXPos - boxes[i][0]) <= distance && fabs(ballYPos - boxes[i][1]) <= distance) {
					boxes[i][2] = 0;
					numberOfBalls--;
				}
			}
		}
		
		al_flip_display();
	}

	system("pause");
	al_destroy_display(display);
	al_destroy_event_queue(queue);

	return 0;
}