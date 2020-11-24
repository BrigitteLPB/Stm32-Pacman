/*
 * Logical.c
 *
 *  Created on: 13 Oct 2020
 *      Author: Théo Malinge--Lecompte
 */
#include"Logical/Logical.h"
// include
#include "Abstract/Joystick/joystick.h"
#include "macro_types.h"
#include "../Abstract/Rand/rand.h"

#include "../Display/Renderer/renderer.h"

// const
#define	TIME_TO_UPDATE		500		// temps en ms avant une update du jeu

// global var
static volatile bool_e init = FALSE;
static volatile bool_e MS_FLAGS;

static volatile bool_e mur = FALSE;
static game_s game;
//static uint16_t s = 10;
static uint16_t score = 0;


// private function
static void PRIVATE_LOGICAL_process_ms();

static void initMAP();
static bool_e getWALL(PACMAN_position pos);
static void sens_fantome(phantom_s *phantom);
static void mouvement(JOYSTICK_direction direction);
static void fantome_mvt();
static state_game VerifierEtatJeu();
//static void refreshCELL(int x, int y);
static bool_e PRIVATE_LOGICAL_phantom_contact(PACMAN_position pos);


// function
void PRIVATE_LOGICAL_process_ms(){
	static uint32_t t=0;

	if(t == TIME_TO_UPDATE){
		MS_FLAGS = TRUE;
		t=0;
	}else{
		t++;
		MS_FLAGS = FALSE;
	}
}

void LOGICAL_init(void){
	if(!init){
		Systick_add_callback_function(&PRIVATE_LOGICAL_process_ms);
		RAND_init();
		init = TRUE;
	}

	initMAP();
	RENDERER_init(&game);
}

void LOGICAL_kill(void){
	Systick_remove_callback_function(&PRIVATE_LOGICAL_process_ms);
	RENDERER_kill();
	init = FALSE;
}

state_game jeu(){
	if(MS_FLAGS){
		mouvement(JOYSTICK_getDirection(JOYSTICK2));
		fantome_mvt();
		RENDERER_show(&game);
	}

	RAND_catch_event();
	return VerifierEtatJeu();
}

state_game VerifierEtatJeu(){
	if (game.pacman.state == DEAD){
		return MENU;
	}else {
		return JEU;
	}
}


void mouvement(JOYSTICK_direction direction){
//	direction = DROITE;		// debug

	static PACMAN_position pos;
	pos = game.pacman.pos;
//	pos.x = 10;
//	pos.y = 10;

//	ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
	switch(direction){
		case BAS:
			pos.y++;
			mur=getWALL(pos);
			pos.y--;
			if(mur==FALSE){
				score++;
				game.map[pos.x][pos.y]= FREE;
//				refreshCELL(x,y);
				pos.y++;
//				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
//				if(PRIVATE_LOGICAL_phantom_contact(pos)){
//					game.pacman.state = DEAD;
//				}
//				else{
//					game.pacman.pos.x = pos.x;
//					game.pacman.pos.y = pos.y;
////					game.map[pos.x][pos.y] = PACMAN;
//				}
			}
			break;
		case DROITE:
			pos.x++;
			mur=getWALL(pos);
			pos.x--;
			if(!mur){
				score++;
				game.map[pos.x][pos.y] = FREE;
//				refreshCELL(x,y);
				pos.x++;
//				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
//				if(PRIVATE_LOGICAL_phantom_contact(pos)){
//					game.pacman.state = DEAD;
//				}
//				else{
//					game.map[pos.x][pos.y] = PACMAN;
//				}
			}
			break;
		case GAUCHE:
			pos.x--;
			mur=getWALL(pos);
			pos.x++;
			if(!mur){
				score++;
				game.map[pos.x][pos.y]  = FREE;
//				refreshCELL(x,y);
				pos.x--;
//				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
//				if(PRIVATE_LOGICAL_phantom_contact(pos)){
//					game.pacman.state = DEAD;
//				}
//				else{
//					game.map[pos.x][pos.y]  = PACMAN;
//				}
			}
			break;
		case HAUT:
			pos.y--;
			mur=getWALL(pos);
			pos.y++;
			if(!mur){
				score++;
				game.map[pos.x][pos.y]  = FREE;
//				refreshCELL(x,y);
				pos.y--;
//				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
//				if(PRIVATE_LOGICAL_phantom_contact(pos)){
//					game.pacman.state = DEAD;
//				}
//				else{
//					game.map[pos.x][pos.y]  = PACMAN;
//				}
			}
			break;
		case NEUTRE:
			break;
	}

	if(PRIVATE_LOGICAL_phantom_contact(pos)){
		game.pacman.state = DEAD;
	}
	else{
		game.map[pos.x][pos.y] = PACMAN;
		game.pacman.pos = pos;
	}

}

bool_e PRIVATE_LOGICAL_phantom_contact(PACMAN_position pos){
	for(uint8_t i=0; i<game.phantom_count; i++){
		if(pos.y == game.phantoms[i].pos.y && pos.x == game.phantoms[i].pos.x){
			return TRUE;
		}
	}
	return FALSE;
}

void fantome_mvt(){
//	static uint16_t x[4]={15,15,16,16};
//	static uint16_t y[4]={11,12,11,12};

//	ILI9341_DrawFilledRectangle((uint16_t)(x[0]*s),(uint16_t)(y[0]*s),(uint16_t)((x[0]+1)*s),(uint16_t)((y[0]+1)*s),ILI9341_COLOR_GREEN);
//	ILI9341_DrawFilledRectangle((uint16_t)(x[1]*s),(uint16_t)(y[1]*s),(uint16_t)((x[1]+1)*s),(uint16_t)((y[1]+1)*s),ILI9341_COLOR_MAGENTA);
//	ILI9341_DrawFilledRectangle((uint16_t)(x[2]*s),(uint16_t)(y[2]*s),(uint16_t)((x[2]+1)*s),(uint16_t)((y[2]+1)*s),ILI9341_COLOR_CYAN);
//	ILI9341_DrawFilledRectangle((uint16_t)(x[3]*s),(uint16_t)(y[3]*s),(uint16_t)((x[3]+1)*s),(uint16_t)((y[3]+1)*s),ILI9341_COLOR_RED);

	for(int i=0;i<game.phantom_count;i++){
		// clear du phantom
		switch(game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y]){
			case FANTOME_WITH_FRUIT:
				game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y] = FRUIT;
				break;
			case FANTOME_WITH_POINT:
				game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y] = POINT;
				break;
			case FANTOME:
				game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y] = FREE;
				break;
			case WALL_WITH_PHANTOM:
				game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y] = WALL;
				break;
			default:
				break;
		}

		sens_fantome(&game.phantoms[i]);

		// assignation
		switch(game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y]){
			case FRUIT:
				game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y] = FANTOME_WITH_FRUIT;
				break;
			case POINT:
				game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y] = FANTOME_WITH_POINT;
				break;
			case FREE:
				game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y] = FANTOME;
				break;
			case WALL:
				game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y] = WALL_WITH_PHANTOM;
				break;
			default:
				break;
		}

//		ILI9341_DrawFilledRectangle((uint16_t)(x[0]*s),(uint16_t)(y[0]*s),(uint16_t)((x[0]+1)*s),(uint16_t)((y[0]+1)*s),ILI9341_COLOR_GREEN);
//		ILI9341_DrawFilledRectangle((uint16_t)(x[1]*s),(uint16_t)(y[1]*s),(uint16_t)((x[1]+1)*s),(uint16_t)((y[1]+1)*s),ILI9341_COLOR_MAGENTA);
//		ILI9341_DrawFilledRectangle((uint16_t)(x[2]*s),(uint16_t)(y[2]*s),(uint16_t)((x[2]+1)*s),(uint16_t)((y[2]+1)*s),ILI9341_COLOR_CYAN);
//		ILI9341_DrawFilledRectangle((uint16_t)(x[3]*s),(uint16_t)(y[3]*s),(uint16_t)((x[3]+1)*s),(uint16_t)((y[3]+1)*s),ILI9341_COLOR_RED);
	}
}

void sens_fantome(phantom_s *phantom){
	uint8_t sens = RAND_get()%4;
	PACMAN_position pos_copy = phantom->pos;

	while(pos_copy.x == phantom->pos.x && pos_copy.y == phantom->pos.y){
		switch(sens){
			case 0 :		//bas
	//			(*y)++;
				mur=getWALL((PACMAN_position){phantom->pos.x,(PACMAN_unit)(phantom->pos.y+1)});
	//			(*y)--;
				if(!mur){
	//				refreshCELL(*x,*y);
	//				(*y)++;
					phantom->pos.y++;
					//ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
	//				if(game.map[*x][*y]  == PACMAN){
	//					game.pacman.state = DEAD;
	//					game.map[*x][*y]  = FANTOME;
	//				}
	//				else{
	//					game.map[*x][*y]  = FANTOME;
	//				}
				}
				break;
			case 1:		//droite
	//			(*x)++;
				mur=getWALL((PACMAN_position){(PACMAN_unit)(phantom->pos.x +1), phantom->pos.y});
	//			(*x)--;
				if(!mur){
	//				refreshCELL(x,y);
	//				(*x)++;
					phantom->pos.x++;
					//ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
	//				if(game.map[*x][*y]  == PACMAN){
	//					game.pacman.state = DEAD;
	//					game.map[*x][*y]  = FANTOME;
	//				}
	//				else{
	//					game.map[*x][*y]  = FANTOME;
	//				}
				}
				break;

			case 2:		//gauche
	//			(*x)--;
				mur=getWALL((PACMAN_position){(PACMAN_unit)(phantom->pos.x-1),phantom->pos.y});
	//			(*x)++;
				if(!mur){
	//				refreshCELL(x,y);
	//				(*x)--;
					phantom->pos.x--;
					//ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
	//				if(game.map[*x][*y]  == PACMAN){
	//					game.pacman.state = DEAD;
	//					game.map[*x][*y]  = FANTOME;
	//				}
	//				else{
	//					game.map[*x][*y]  = FANTOME;
	//				}
				}
				break;

			case 3:		//haut
	//			(*y)--;
				mur=getWALL((PACMAN_position){phantom->pos.x,(PACMAN_unit)(phantom->pos.y-1)});
	//			(*y)++;
				if(!mur){
	//				refreshCELL(x,y);
	//				(*y)--;
					phantom->pos.y--;
					//ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
	//				if(game.map[*x][*y]  == PACMAN){
	//					game.pacman.state = DEAD;
	//					game.map[*x][*y]  = FANTOME;
	//				}
	//				else{
	//					game.map[*x][*y]  = FANTOME;
	//				}
				}
				break;
		}

		sens = (uint8_t)((sens+1)%4);
	}

	if(game.pacman.pos.x == phantom->pos.x && game.pacman.pos.y == phantom->pos.y){
		game.pacman.state = DEAD;
	}

//	switch(game.map[phantom->pos.x][phantom->pos.y]){
//		case POINT:
//			game.map[phantom->pos.x][phantom->pos.y] = FANTOME_WITH_POINT;
//			break;
//		case FRUIT:
//			game.map[phantom->pos.x][phantom->pos.y] = FANTOME_WITH_FRUIT;
//			break;
//		default:
//			game.map[phantom->pos.x][phantom->pos.y] = FREE;
//			break;
//	}
}

void initMAP(){
	// pacman
	game.pacman.score = 0;
	game.pacman.state = ALIVE;
	game.pacman.pos.y = 1;
	game.pacman.pos.x = 1;

	for(int i=0;i<LENGTH;i++){				//point + contours
		for(int j=0;j<HEIGHT;j++){
			game.map[i][j] = POINT;
			game.map[0][j] = WALL;
			game.map[i][HEIGHT-1] = WALL;
			game.map[i][0] = WALL;
			game.map[LENGTH-1][j] = WALL;
		}
	}

	game.phantom_count = 4;
	static uint8_t phantom_count = 0;		//les murs
	for(int x=0;x<2;x++){					//carre
		for(int y=0;y<2;y++){
			// phantoms
			game.map[15+x][11+y] = WALL_WITH_PHANTOM;
			game.phantoms[phantom_count].pos.x = (PACMAN_unit)(15+x);
			game.phantoms[phantom_count].pos.y = (PACMAN_unit)(11+y);
			phantom_count++;


			game.map[2+x][2+y] = WALL;
			game.map[28+x][2+y] = WALL;
			game.map[2+x][20+y] = WALL;
			game.map[28+x][20+y] = WALL;
			game.map[15+x][8+y] = WALL;
			game.map[15+x][14+y] = WALL;
		}
	}
	for(int y=7;y<17;y++){					//colonne de 10
		game.map[2][y] = WALL;
		game.map[29][y] = WALL;
	}
	for(int i=0;i<6;i++){					//longueur de 6
		game.map[i+13][2] = WALL;
		game.map[i+13][21] = WALL;

		game.map[13][i+4] = WALL;
		game.map[13][i+14] = WALL;
		game.map[18][i+4] = WALL;
		game.map[18][i+14] = WALL;

		game.map[8][i+9] = WALL;
		game.map[23][i+9] = WALL;
	}
	for(int i=0;i<4;i++){					//longueur de 4
		game.map[i+3][5] = WALL;
		game.map[i+3][11] = WALL;
		game.map[i+3][12] = WALL;
		game.map[i+3][18] = WALL;
		game.map[i+25][5] = WALL;
		game.map[i+25][11] = WALL;
		game.map[i+25][12] = WALL;
		game.map[i+25][18] = WALL;

		game.map[i+8][2] = WALL;
		game.map[i+20][2] = WALL;
		game.map[i+8][21] = WALL;
		game.map[i+20][21] = WALL;
	}
	for(int i=0;i<3;i++){					//longueur de 3
		game.map[i+10][4] = WALL;
		game.map[i+19][4] = WALL;
		game.map[i+10][19] = WALL;
		game.map[i+19][19] = WALL;

		game.map[5][i+1] = WALL;
		game.map[6][i+1] = WALL;
		game.map[25][i+1] = WALL;
		game.map[26][i+1] = WALL;

		game.map[5][i+20] = WALL;
		game.map[6][i+20] = WALL;
		game.map[25][i+20] = WALL;
		game.map[26][i+20] = WALL;

		game.map[8][i+3] = WALL;
		game.map[23][i+3] = WALL;
		game.map[8][i+18] = WALL;
		game.map[23][i+18] = WALL;

		game.map[15][i+4] = WALL;
		game.map[16][i+4] = WALL;
		game.map[15][i+17] = WALL;
		game.map[16][i+17] = WALL;

		game.map[12][i+8] = WALL;
		game.map[19][i+8] = WALL;
		game.map[12][i+13] = WALL;
		game.map[19][i+13] = WALL;

		game.map[4][i+7] = WALL;
		game.map[6][i+7] = WALL;
		game.map[25][i+7] = WALL;
		game.map[27][i+7] = WALL;
		game.map[4][i+14] = WALL;
		game.map[6][i+14] = WALL;
		game.map[25][i+14] = WALL;
		game.map[27][i+14] = WALL;
	}
	for(int i=0;i<2;i++){					//longueur de 2
		game.map[i+9][9] = WALL;
		game.map[i+21][9] = WALL;
		game.map[i+9][14] = WALL;
		game.map[i+21][14] = WALL;

		game.map[i+9][7] = WALL;
		game.map[i+10][6] = WALL;
		game.map[i+20][17] = WALL;
		game.map[i+21][16] = WALL;
		game.map[i+20][6] = WALL;
		game.map[i+21][7] = WALL;
		game.map[i+9][16] = WALL;
		game.map[i+10][17] = WALL;

		game.map[10][i+11] = WALL;
		game.map[21][i+11] = WALL;

		game.map[14][i+11] = WALL;
		game.map[17][i+11] = WALL;
	}
											//longueur de 1
	game.map[1][5] = WALL;
	game.map[1][18] = WALL;
	game.map[30][5] = WALL;
	game.map[30][18] = WALL;
	game.map[7][7] = WALL;
	game.map[7][16] = WALL;
	game.map[24][7] = WALL;
	game.map[24][16] = WALL;
}

void refreshMAP(){
	RENDERER_show(&game);
}

//void refreshCELL(int x, int y){
//	if(game.map[x][y] == OBJECT){
//		ILI9341_DrawPixel((uint16_t)((x*10)+5),(uint16_t)((y*10)+5),ILI9341_COLOR_WHITE);
//	}
//	else{
//		ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_BLACK);
//	}
//
//}

bool_e getWALL(PACMAN_position pos){
	return game.map[pos.x][pos.y] == WALL || game.map[pos.x][pos.y] == WALL_WITH_PHANTOM;
}
