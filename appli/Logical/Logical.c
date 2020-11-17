
/*
 * Logical.c
 *
 *  Created on: 13 Oct 2020
 *      Author: Théo Malinge--Lecompte
 */

#include"Logical/Logical.h"
#include "Abstract/Joystick/joystick.h"
#include "stdbool.h"
#include <stdlib.h>

volatile static bool mur = false;
static game_s game;
static uint16_t s=10;
static uint16_t score=0;

static bool getWALL(int x, int y);
static void sens_fantome();
static void mouvement(JOYSTICK_direction direction);
static void fantome_mvt();
static state_game VerifierEtatJeu();
static void refreshCELL(int x, int y);

state_game jeu(){
	mouvement(JOYSTICK_getDirection(JOYSTICK2));
	fantome_mvt();
	return VerifierEtatJeu();
}

state_game VerifierEtatJeu(){
	if (game.pacman->state == DEAD){
		return MENU;
	}
	else {
		return JEU;
	}

}


void mouvement(JOYSTICK_direction direction){
	static uint16_t x=10;
	static uint16_t y=10;
	ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
	switch(direction){
		case BAS:
			y++;
			mur=getWALL(x,y);
			y--;
			if(mur==false){
				score++;
				game.map[x][y]= FREE;
				refreshCELL(x,y);
				y++;
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
				if(game.map[x][y] == FANTOME){
					game.pacman->state = DEAD;
				}
				else{
					game.map[x][y] = PACMAN;
				}

			}
			break;
		case DROITE:
			x++;
			mur=getWALL(x,y);
			x--;
			if(mur==false){
				score++;
				game.map[x][y] = FREE;
				refreshCELL(x,y);
				x++;
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
				if(game.map[x][y] == FANTOME){
					game.pacman->state = DEAD;
				}
				else{
					game.map[x][y] = PACMAN;
				}
			}
			break;
		case GAUCHE:
			x--;
			mur=getWALL(x,y);
			x++;
			if(mur==false){
				score++;
				game.map[x][y]  = FREE;
				refreshCELL(x,y);
				x--;
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
				if(game.map[x][y]  == FANTOME){
					game.pacman->state = DEAD;
				}
				else{
					game.map[x][y]  = PACMAN;
				}
			}
			break;
		case HAUT:
			y--;
			mur=getWALL(x,y);
			y++;
			if(mur==false){
				score++;
				game.map[x][y]  = FREE;
				refreshCELL(x,y);
				y--;
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
				if(game.map[x][y]  == FANTOME){
					game.pacman->state = DEAD;
				}
				else{
					game.map[x][y]  = PACMAN;
				}
			}
			break;
		case NEUTRE:
			break;
	}
}

void fantome_mvt(){
	static uint16_t x[4]={15,15,16,16};
	static uint16_t y[4]={11,12,11,12};
	ILI9341_DrawFilledRectangle((uint16_t)(x[0]*s),(uint16_t)(y[0]*s),(uint16_t)((x[0]+1)*s),(uint16_t)((y[0]+1)*s),ILI9341_COLOR_GREEN);
	ILI9341_DrawFilledRectangle((uint16_t)(x[1]*s),(uint16_t)(y[1]*s),(uint16_t)((x[1]+1)*s),(uint16_t)((y[1]+1)*s),ILI9341_COLOR_MAGENTA);
	ILI9341_DrawFilledRectangle((uint16_t)(x[2]*s),(uint16_t)(y[2]*s),(uint16_t)((x[2]+1)*s),(uint16_t)((y[2]+1)*s),ILI9341_COLOR_CYAN);
	ILI9341_DrawFilledRectangle((uint16_t)(x[3]*s),(uint16_t)(y[3]*s),(uint16_t)((x[3]+1)*s),(uint16_t)((y[3]+1)*s),ILI9341_COLOR_RED);
	for(int i=0;i<4;i++){
		sens_fantome(&(x[i]),&(y[i]));
		ILI9341_DrawFilledRectangle((uint16_t)(x[0]*s),(uint16_t)(y[0]*s),(uint16_t)((x[0]+1)*s),(uint16_t)((y[0]+1)*s),ILI9341_COLOR_GREEN);
		ILI9341_DrawFilledRectangle((uint16_t)(x[1]*s),(uint16_t)(y[1]*s),(uint16_t)((x[1]+1)*s),(uint16_t)((y[1]+1)*s),ILI9341_COLOR_MAGENTA);
		ILI9341_DrawFilledRectangle((uint16_t)(x[2]*s),(uint16_t)(y[2]*s),(uint16_t)((x[2]+1)*s),(uint16_t)((y[2]+1)*s),ILI9341_COLOR_CYAN);
		ILI9341_DrawFilledRectangle((uint16_t)(x[3]*s),(uint16_t)(y[3]*s),(uint16_t)((x[3]+1)*s),(uint16_t)((y[3]+1)*s),ILI9341_COLOR_RED);
	}
}

void sens_fantome(uint16_t* x,uint16_t* y){
	int sens =rand()%4;
	switch(sens){
		case 0 :		//bas
			(*y)++;
			mur=getWALL(*x,*y);
			(*y)--;
			if(!mur){
				refreshCELL(x,y);
				(*y)++;
				//ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
				if(game.map[*x][*y]  == PACMAN){
					game.pacman->state = DEAD;
					game.map[*x][*y]  = FANTOME;
				}
				else{
					game.map[*x][*y]  = FANTOME;
				}
			}
			break;
		case 1:		//droite
			(*x)++;
			mur=getWALL(*x,*y);
			(*x)--;
			if(!mur){
				refreshCELL(x,y);
				(*x)++;
				//ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
				if(game.map[*x][*y]  == PACMAN){
					game.pacman->state = DEAD;
					game.map[*x][*y]  = FANTOME;
				}
				else{
					game.map[*x][*y]  = FANTOME;
				}
			}
			break;

		case 2:		//gauche
			(*x)--;
			mur=getWALL(*x,*y);
			(*x)++;
			if(!mur){
				refreshCELL(x,y);
				(*x)--;
				//ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
				if(game.map[*x][*y]  == PACMAN){
					game.pacman->state = DEAD;
					game.map[*x][*y]  = FANTOME;
				}
				else{
					game.map[*x][*y]  = FANTOME;
				}
			}
			break;

		case 3:		//haut
			(*y)--;
			mur=getWALL(*x,*y);
			(*y)++;
			if(!mur){
				refreshCELL(x,y);
				(*y)--;
				//ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
				if(game.map[*x][*y]  == PACMAN){
					game.pacman->state = DEAD;
					game.map[*x][*y]  = FANTOME;
				}
				else{
					game.map[*x][*y]  = FANTOME;
				}
			}
			break;
	}
}

void initMAP(){
	for(int i=0;i<LENGTH;i++){				//point + contours
		for(int j=0;j<HEIGHT;j++){
			game.map[i][j] = OBJECT;
			game.map[0][j] = WALL;
			game.map[i][HEIGHT-1] = WALL;
			game.map[i][0] = WALL;
			game.map[LENGTH-1][j] = WALL;
		}
	}

											//les murs
	for(int x=0;x<2;x++){					//carrÃ©
		for(int y=0;y<2;y++){
			game.map[15+x][11+y] = WALL_WITH_PHANTOM;

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
		game.map[i+27][7] = WALL;
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
	for(int i=0;i<LENGTH;i++){
		for(int j=0;j<HEIGHT;j++){
			if(game.map[i][j] == WALL || game.map[i][j] == WALL_WITH_PHANTOM){
				ILI9341_DrawFilledRectangle((uint16_t)(i*10),(uint16_t)(j*10),(uint16_t)((i+1)*10),(uint16_t)((j+1)*10),ILI9341_COLOR_BLUE);
			}
			else if(game.map[i][j] == OBJECT){
				ILI9341_DrawPixel((uint16_t)((i*10)+5),(uint16_t)((j*10)+5),ILI9341_COLOR_WHITE);
			}
			else{
				ILI9341_DrawFilledRectangle((uint16_t)(i*10),(uint16_t)(j*10),(uint16_t)((i+1)*10),(uint16_t)((j+1)*10),ILI9341_COLOR_BLACK);
			}
		}
	}
}

void refreshCELL(int x, int y){
	if(game.map[x][y] == OBJECT){
		ILI9341_DrawPixel((uint16_t)((x*10)+5),(uint16_t)((y*10)+5),ILI9341_COLOR_WHITE);
	}
	else{
		ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_BLACK);
	}

}

bool getWALL(int x, int y){
	if(game.map[x][y]  == WALL || game.map[x][y]  == WALL_WITH_PHANTOM){
		return true;
	}else{
		return false;
	}
}
