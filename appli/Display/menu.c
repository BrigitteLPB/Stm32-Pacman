#include "Display/menu.h"

static void winMenu();
static void initMenu();

static uint16_t score = 0;



void menu(){
	static state_game state = INIT;
	static bool_e bas;

	switch(state){
		case INIT:
			state = MENU;
			bas = FALSE;
			break;

		case MENU:

			if(JOYSTICK_getDirection(JOYSTICK2)== DROITE || JOYSTICK_getDirection(JOYSTICK1) == DROITE){
				LOGICAL_init(bas);
				state = JEU;
			}
			else if (JOYSTICK_getDirection(JOYSTICK2)== BAS || JOYSTICK_getDirection(JOYSTICK1) == BAS){
				TFT_text_s text3 = TFT_make_text("  ", (pos_s){60,100}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
				TFT_put_text(&text3);
				TFT_text_s text4 = TFT_make_text("->", (pos_s){100,100}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
				TFT_put_text(&text4);

				bas = TRUE;
			}
			else if (JOYSTICK_getDirection(JOYSTICK2)== HAUT || JOYSTICK_getDirection(JOYSTICK1) == HAUT){
				TFT_text_s text3 = TFT_make_text("->", (pos_s){60,100}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
				TFT_put_text(&text3);
				TFT_text_s text4 = TFT_make_text("  ", (pos_s){100,100}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
				TFT_put_text(&text4);

				bas = FALSE;
			}
			break;

		case JEU:
			state = jeu(&score);
			if (state == MENU){
				LOGICAL_kill();
				initMenu();
				bas = FALSE;
			}else if(state == WIN){
				LOGICAL_kill();
				winMenu();
			}
			break;

		case WIN:
			if(JOYSTICK_getDirection(JOYSTICK2)== DROITE || JOYSTICK_getDirection(JOYSTICK1) == DROITE){
				state = MENU;
				initMenu();
				bas = FALSE;
			}
			break;
	}

}

void initMenu(){
	TFT_clear(COLOR_BLACK);
	TFT_text_s text = TFT_make_text("New game", (pos_s){60,140}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
	TFT_put_text(&text);
	TFT_text_s text2 = TFT_make_text("New game+", (pos_s){100,140}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
	TFT_put_text(&text2);
	TFT_text_s text3 = TFT_make_text("->", (pos_s){60,100}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
	TFT_put_text(&text3);
	char text_score_str[16];
	sprintf(text_score_str, "score: %d", score);

	TFT_text_s text_score = TFT_make_text(text_score_str, (pos_s){140,100}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
	TFT_put_text(&text_score);

}

void winMenu(){
	TFT_clear(COLOR_BLACK);
	TFT_text_s text = TFT_make_text("You win !", (pos_s){60,140}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);

	TFT_put_text(&text);
}
