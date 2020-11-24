#include "Display/menu.h"



void menu(){
	static state_game state = MENU;
	switch(state){
		case MENU:
			if(JOYSTICK_getDirection(JOYSTICK2)== DROITE){
				LOGICAL_init();
				state = JEU;
			}
			break;
		case JEU:
			state = jeu();
			if (state == MENU){
				initMenu();
			}
			break;
	}

}

void initMenu(){
	ILI9341_DrawFilledRectangle((uint16_t)(0),(uint16_t)(0),(uint16_t)(320),(uint16_t)(240),ILI9341_COLOR_BLACK);
	TFT_text_s text = TFT_make_text("New game", (pos_s){60,140}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
	TFT_put_text(&text);
}
