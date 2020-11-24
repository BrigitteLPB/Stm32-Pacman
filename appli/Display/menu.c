#include "Display/menu.h"

static void winMenu();
static void initMenu();

static uint16_t score = 0;

void menu(){
	static state_game state = INIT;
	switch(state){
		case INIT:
			state = MENU;
			initMenu();
			break;

		case MENU:
			if(JOYSTICK_getDirection(JOYSTICK2)== DROITE || JOYSTICK_getDirection(JOYSTICK1) == DROITE){
				LOGICAL_init();
				state = JEU;
			}
			break;

		case JEU:
			state = jeu(&score);
			if (state == MENU){
				LOGICAL_kill();
				initMenu();
			}else if(state == WIN){
				LOGICAL_kill();
				winMenu();
			}
			break;

		case WIN:
			if(JOYSTICK_getDirection(JOYSTICK2)== DROITE){
				state = INIT;
			}
			break;
	}

}

void initMenu(){
//	ILI9341_DrawFilledRectangle((uint16_t)(0),(uint16_t)(0),(uint16_t)(320),(uint16_t)(240),ILI9341_COLOR_BLACK);
	TFT_clear(COLOR_BLACK);
	TFT_text_s text = TFT_make_text("New game", (pos_s){60,140}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
	TFT_put_text(&text);
	char text_score_str[16];
	sprintf(text_score_str, "score: %d", score);

	TFT_text_s text_score = TFT_make_text(text_score_str, (pos_s){100,100}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
	TFT_put_text(&text_score);

}

void winMenu(){
	TFT_clear(COLOR_BLACK);
	TFT_text_s text = TFT_make_text("You win !", (pos_s){60,140}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
//	char text_score_str[16];
//	sprintf(text_score_str, "score: %d", score);

//	TFT_text_s text_score = TFT_make_text(text_score_str, (pos_s){100,100}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);

	TFT_put_text(&text);
//	TFT_put_text(&text_score);
}
