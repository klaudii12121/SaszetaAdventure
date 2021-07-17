#include <iostream>
#include <cstdlib>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5//allegro_ttf.h>

	//zmienne
int height = 640, width = 880, x = 100, y = 200, speed = 2, frame = 0, ex = 200, ey = 150;
int eex = 450, eey = 510, eeex = 450, eeey = 285, lifes = 3, points = 0;
bool t = true, active = false, kolizja = false, vertical = true, horizontal = true, horizontal2 = true;
bool o_saszeta = true, menu = true, score = true;
const float FPS = 60.0;

bool col(int &x, int &y, int ex, int ey, int w, int h) {
	if (x + w < ex  || x > ex + w || y + h < ey || y > ey + h ) {
		return 0;
	}
	else return 1;
}

int polozenie(int& x, int& y) {
	if (x <= 50 && y <= 290)  x = 50;
	if (x >= 590 && x <= 710 && y <= 250) x = 710;
	if (x <= 700 && y >= 300 && y <= 440) x = 700;
	if (y >= 290 && y <= 500 && x >= 50 && x <= 280) y = 550, x = 600;
	if (y <= 290 && x >= 500 && x <= 590) y = 290;
	if (x >= 300 && x <= 310 && y <= 250) x = 300;
	if (x >= 790 && x <= 810 && y <= 300) x = 790;
	if (x >= 710 && y >= 300 && y <= 550) x = 710;
	if (x <= 290 && y >= 480 && y <= 560) x = 290;
	if (x <= 700 && x >= 600 && y >= 300 && y <= 480) x = 700;
	if (y <= 120 && x >= 25 && x <= 325) y = 120;
	if (y <= 260 && x >= 325 && x <= 460)  y = 260;
	if (y <= 240 && x >= 460 && x <= 500) y = 240;
	if (y <= 260 && x >= 500 && x <= 700)  y = 260;
	if (y <= 170 && x >= 680)  y = 170;
	if (y <= 485 && y >= 450 && x <= 680 && x >= 530) y = 485;
	if (y <= 485 && y >= 300 && x <= 500 && x >= 270) y = 485;
	if (y <= 460 && y >= 300 && x <= 530 && x >= 500) y = 460;
	if (y <= 505 && y >= 485 && x <= 645 && x >= 560) y = 505;
	if (y > 270 && y < 310 && x >= 25 && x <= 590) y = 270;
	if (y > 290 && y < 310 && x >= 590 && x <= 680) y = 290;
	if (y > 290 && y < 310 && x >= 740) y = 290;
	if (y > 550 && x >= 500) y = 550;
	if (y > 530 && x < 500) y = 530;
	return 0;
}

int main()
{
	//instalowanie
	al_init();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY* display = al_create_display(width, height);
	ALLEGRO_EVENT_QUEUE* events = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP* menuscr = al_load_bitmap("assets/menu.png");
	ALLEGRO_BITMAP* scorescr = al_load_bitmap("assets/score.png");
	ALLEGRO_BITMAP* player = al_load_bitmap("assets/kotki.png");
	ALLEGRO_BITMAP* enemy = al_load_bitmap("assets/kobieta.png");
	ALLEGRO_BITMAP* enemy2 = al_load_bitmap("assets/mezczyzna.png");
	ALLEGRO_BITMAP* enemy3 = al_load_bitmap("assets/dziecko.png");
	ALLEGRO_BITMAP* home = al_load_bitmap("assets/domek.png");
	ALLEGRO_BITMAP* saszeta = al_load_bitmap("assets/saszeta.png");
	ALLEGRO_FONT* text = al_load_font("atari.ttf", 22, 0);

	srand(time(NULL));
	int sx = rand() % 350 + 150;
	int sy = rand() % 350 + 150;

	al_set_window_title(display, "Saszeta Adventure");
	al_register_event_source(events, al_get_keyboard_event_source());
	al_register_event_source(events, al_get_timer_event_source(timer));
	al_start_timer(timer);

	//Ekran menu
	while (menu) {

		ALLEGRO_EVENT ev;
		al_wait_for_event(events, &ev);
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		//Reagowanie na klawisze
		y = 530;
		sy = 550;
		sx = 500;
		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
		{
			menu = false;
			t = false;
			score = false;
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_ENTER))
		{
			menu = false;
			o_saszeta = false;
		}
		al_draw_bitmap(menuscr, 0, 0, 0);//Bitmapa menu

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{

			x = x + speed * 1.5;

			frame += 2;
			if (frame > 60) frame = 0;

			if (frame < 20) al_draw_bitmap_region(player, 0, 100, 47, 50, x, y, 0);
			else if (frame >= 20 && frame < 40) al_draw_bitmap_region(player, 47, 100, 48, 50, x, y, 0);
			else if (frame >= 40 && frame <= 60) al_draw_bitmap_region(player, 95, 100, 48, 50, x, y, 0);

			if (col(x, y, sx, sy, 20, 30)) {
				kolizja = true;
			}
			if (!kolizja) {
				o_saszeta = true;
			}
			else {
				o_saszeta = false;
			}
			if (o_saszeta == true) {
				al_draw_bitmap_region(saszeta,-20,-10,30,23, sx, sy, 0);
			}
			if (x >= 880) x = -20;

			al_flip_display();
		}
	}
	x = 100, y = 200;
	sx = rand() % 350 + 150;
	sy = rand() % 350 + 150;
	//Gra wlasciwa
	while (t) {
	
		ALLEGRO_EVENT ev;
		al_wait_for_event(events, &ev);
		
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		//Reagowanie na klawisze/ poruszanie kitku
		
			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
			{
				t = false;
				menu = false;
			}
			
			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
			{
				y = y + speed;
				active = true;
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_UP))
			{
				y = y - speed;
				active = true;
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			{
				x = x + speed;
				active = true;
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
			{
				x = x - speed;
				active = true;
			}
			else
				active = false;

		//Poruszanie siê przeciwnikow
			//Przeciwnik - kobieta
				if (vertical == false && ey <= 250) {
					ey = ey + speed;
				}
				else vertical = true;
				if (vertical == true && ey >= 100) {
					ey = ey - speed;
				}
				else vertical = false;
			//Przeciwnik - mezczyzna
				if (horizontal == false && eex <= 680) {
					eex = eex + speed;
				}
				else horizontal = true;
				if (horizontal == true && eex >= 350) {
					eex = eex - speed;
				}
				else horizontal = false;
			//Przeciwnik - dziecko
				if (horizontal2 == false && eeex <= 590) {
					eeex = eeex + speed;
				}
				else horizontal2 = true;
				if (horizontal2 == true && eeex >= 350) {
					eeex = eeex - speed;
				}
				else horizontal2 = false;

		// Kolizja 
			//Kolizja z kobieta
				if (col(x, y, ex, ey, 30, 40)) {
					sx = rand() % 350 + 150;
					sy = rand() % 350 + 150;
					kolizja = true;
					if (kolizja) x = 100, y = 200, lifes = lifes -1;
				}
			//Kolizja z mezczyzna
				if (col(x, y, eex, eey, 30, 40)) {
					sx = rand() % 350 + 150;
					sy = rand() % 350 + 150;
					kolizja = true;
					if (kolizja) x = 100, y = 200, lifes = lifes - 1;
				}
			//Kolizja z dzieckiem
				if (col(x, y, eeex, eeey, 30, 40)) {
					sx = rand() % 350 + 150;
					sy = rand() % 350 + 150;
					kolizja = true;
					if (kolizja) x = 100, y = 200, lifes = lifes - 1;
				}
			//Kolizja z saszeta
				if (col(x, y, sx, sy, 20, 30)) {
					sx = rand() % 350 + 150;
					sy = rand() % 350 + 150;
					kolizja = true;
					if (kolizja) points = points + 50;
				}
			frame += 2;
			if (frame > 60) frame = 0;

		//Znikanie i pojawianie sie nowej saszety wraz z kolizja (utrata zycia/zebraniem saszety)
			if (!kolizja) {
				o_saszeta = true;
			}
			else {
				o_saszeta = false;
			}
				o_saszeta = true;
				
		//Ograniczenia wzglêdem okna/planszy
				polozenie(x, y); 
				polozenie(sx, sy);
						
		//Zycia
		if (lifes == 0) break;

		//Timer/ animacja chodzenia
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			al_clear_to_color(al_map_rgb(162, 234, 255));
			al_draw_bitmap(home, 0, 0, 0); //bitmapa t³a
			al_draw_textf(text, al_map_rgb(255,255,255), 50, 440, 0, "Zycia: %i ", lifes);
			al_draw_textf(text, al_map_rgb(255,255,255), 50, 490, 0, "Punkty:");
			al_draw_textf(text, al_map_rgb(255,255,255), 50, 530, 0, "%i ", points);
			
			//bitmapa - saszeta
			if (o_saszeta == true) {
				al_draw_bitmap_region(saszeta, -20, -20, 30, 33, sx, sy, 0);
			}
			// bitmapa - kobieta
			if (vertical==false) { 
				if (frame < 20) al_draw_bitmap_region(enemy, 0, 0, 50, 75, ex, ey, 0);
				else if (frame >= 20 && frame < 40) al_draw_bitmap_region(enemy, 50, 0, 44, 75, ex, ey, 0);
				else if (frame >= 40 && frame <= 60) al_draw_bitmap_region(enemy, 100, 0, 44, 75, ex, ey, 0);
			}
			if (vertical == true) {
				if (frame < 20) al_draw_bitmap_region(enemy, 0, 220, 50, 80, ex, ey, 0);
				else if (frame >= 20 && frame < 40) al_draw_bitmap_region(enemy, 50, 220, 44, 70, ex, ey, 0);
				else if (frame >= 40 && frame <= 60) al_draw_bitmap_region(enemy, 100, 220, 44, 70, ex, ey, 0);
			}
			// bitmapa - mezczyzna
			if (horizontal == false) {
				if (frame < 20) al_draw_bitmap_region(enemy2, 0, 145, 50, 70, eex, eey, 0);
				else if (frame >= 20 && frame < 40) al_draw_bitmap_region(enemy2, 50, 145, 44, 70, eex, eey, 0);
				else if (frame >= 40 && frame <= 60) al_draw_bitmap_region(enemy2, 100, 145, 44, 70, eex, eey, 0);
			}
			if (horizontal == true) {
				if (frame < 20) al_draw_bitmap_region(enemy2, 0, 75, 50, 70, eex, eey, 0);
				else if (frame >= 20 && frame < 40) al_draw_bitmap_region(enemy2, 50, 75, 44, 70, eex, eey, 0);
				else if (frame >= 40 && frame <= 60) al_draw_bitmap_region(enemy2, 100, 75, 44, 70, eex, eey, 0);
			}
			//bitmapa - dziecko
			if (horizontal2 == false) {
				if (frame < 20) al_draw_bitmap_region(enemy3, 0, 90, 27, 30, eeex, eeey, 0);
				else if (frame >= 20 && frame < 40) al_draw_bitmap_region(enemy3, 27, 90, 27, 30, eeex, eeey, 0);
				else if (frame >= 40 && frame <= 60) al_draw_bitmap_region(enemy3, 54, 90, 27, 30, eeex, eeey, 0);
			}
			if (horizontal2 == true) {
				if (frame < 20) al_draw_bitmap_region(enemy3, 0, 60, 27, 30, eeex, eeey, 0);
				else if (frame >= 20 && frame < 40) al_draw_bitmap_region(enemy3, 27, 60, 27, 30, eeex, eeey, 0);
				else if (frame >= 40 && frame <= 60) al_draw_bitmap_region(enemy3, 54, 60, 27, 30, eeex, eeey, 0);
			}
			//bitmapa - kitku
				// gdy jest aktywny
			if (active) { 
				if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
					if (frame < 20) al_draw_bitmap_region(player, 0, 0, 50, 50, x, y, 0);
					else if (frame >= 20 && frame < 40) al_draw_bitmap_region(player, 50, 0, 44, 50, x, y, 0);
					else if (frame >= 40 && frame <= 60) al_draw_bitmap_region(player, 100, 0, 44, 50, x, y, 0);
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
					if (frame < 20) al_draw_bitmap_region(player, 0, 150, 50, 45, x, y, 0);
					else if (frame >= 20 && frame < 40) al_draw_bitmap_region(player, 45, 150, 44, 45, x, y, 0);
					else if (frame >= 40 && frame <= 60) al_draw_bitmap_region(player, 90, 150, 44, 45, x, y, 0);
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
					if (frame < 20) al_draw_bitmap_region(player, 0, 100, 47, 50, x, y, 0);
					else if (frame >= 20 && frame < 40) al_draw_bitmap_region(player, 47, 100, 48, 50, x, y, 0);
					else if (frame >= 40 && frame <= 60) al_draw_bitmap_region(player, 95, 100, 48, 50, x, y, 0);
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
					if (frame < 20) al_draw_bitmap_region(player, 0, 50, 47, 50, x, y, 0);
					else if (frame >= 20 && frame < 40) al_draw_bitmap_region(player, 47, 50, 48, 50, x, y, 0);
					else if (frame >= 40 && frame <= 60) al_draw_bitmap_region(player, 95, 50, 48, 50, x, y, 0);
				}
			}
				//gdy !active, czyli postaæ stoi
			else {
				al_draw_bitmap_region(player, 50, 0, 44, 50, x, y, 0); 
			}
		}
		al_flip_display();
	}

	//Ekran wynikow
	if (t) {
		while (score) {

			ALLEGRO_EVENT ev;
			al_wait_for_event(events, &ev);
			ALLEGRO_KEYBOARD_STATE keyState;
			al_get_keyboard_state(&keyState);

			//Reagowanie na ESC
			if (al_key_down(&keyState, ALLEGRO_KEY_ENTER) || (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)))
			{
				score = false;
				t = false;
			}

			al_draw_bitmap(scorescr, 0, 0, 0);//Bitmapa ekranu wynikow
			al_draw_textf(text, al_map_rgb(255, 255, 255), 270, 320, 0, "Uzyskane punkty:", points);
			al_draw_textf(text, al_map_rgb(255, 255, 255), 430, 350, 0, "%i", points);
			al_flip_display();
		}
	}
	//czyszczenie pamiêci
	al_destroy_display(display);
	al_destroy_event_queue(events);
	al_destroy_timer(timer);
	al_destroy_font(text);
	al_destroy_bitmap(menuscr);
	al_destroy_bitmap(scorescr);
	al_destroy_bitmap(player);
	al_destroy_bitmap(home);
	al_destroy_bitmap(enemy);
	al_destroy_bitmap(enemy2);
	al_destroy_bitmap(enemy3);
	al_destroy_bitmap(saszeta);
	return 0;
}

