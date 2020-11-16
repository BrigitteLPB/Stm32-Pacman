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

static bool getWALL(int x, int y);
static void sens_fantome();


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
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_BLACK);
				game.map[x][y].type = FREE;
				y++;
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
				if(game.map[x][y].type == FANTOME){
					game.pacman->state = DEAD;
				}
				else{
					game.map[x][y].type = PACMAN;
				}

			}
			break;
		case DROITE:
			x++;
			mur=getWALL(x,y);
			x--;
			if(mur==false){
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_BLACK);
				game.map[x][y].type = FREE;
				x++;
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
				if(game.map[x][y].type == FANTOME){
					game.pacman->state = DEAD;
				}
				else{
					game.map[x][y].type = PACMAN;
				}
			}
			break;
		case GAUCHE:
			x--;
			mur=getWALL(x,y);
			x++;
			if(mur==false){
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_BLACK);
				game.map[x][y].type = FREE;
				x--;
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
				if(game.map[x][y].type == FANTOME){
					game.pacman->state = DEAD;
				}
				else{
					game.map[x][y].type = PACMAN;
				}
			}
			break;
		case HAUT:
			y--;
			mur=getWALL(x,y);
			y++;
			if(mur==false){
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_BLACK);
				game.map[x][y].type = FREE;
				y--;
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
				if(game.map[x][y].type == FANTOME){
					game.pacman->state = DEAD;
				}
				else{
					game.map[x][y].type = PACMAN;
				}
			}
			break;
		case NEUTRE:
			break;
	}
}

void fantome_mvt(){
	static uint16_t x[4]={1,2,3,4};
	static uint16_t y[4]={1,2,3,4};
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
				ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_BLACK);
				(*y)++;
				ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
				if(game.map[*x][*y].type == PACMAN){
					game.pacman->state = DEAD;
					game.map[*x][*y].type = FANTOME;
				}
				else{
					game.map[*x][*y].type = FANTOME;
				}
			}
			break;
		case 1:		//droite
			(*x)++;
			mur=getWALL(*x,*y);
			(*x)--;
			if(!mur){
				ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_BLACK);
				(*x)++;
				ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
				if(game.map[*x][*y].type == PACMAN){
					game.pacman->state = DEAD;
					game.map[*x][*y].type = FANTOME;
				}
				else{
					game.map[*x][*y].type = FANTOME;
				}
			}
			break;

		case 2:		//gauche
			(*x)--;
			mur=getWALL(*x,*y);
			(*x)++;
			if(!mur){
				ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_BLACK);
				(*x)--;
				ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
				if(game.map[*x][*y].type == PACMAN){
					game.pacman->state = DEAD;
					game.map[*x][*y].type = FANTOME;
				}
				else{
					game.map[*x][*y].type = FANTOME;
				}
			}
			break;

		case 3:		//haut
			(*y)--;
			mur=getWALL(*x,*y);
			(*y)++;
			if(!mur){
				ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_BLACK);
				(*y)--;
				ILI9341_DrawFilledRectangle((uint16_t)((*x)*s),(uint16_t)((*y)*s),(uint16_t)(((*x)+1)*s),(uint16_t)(((*y)+1)*s),ILI9341_COLOR_GREEN);
				if(game.map[*x][*y].type == PACMAN){
					game.pacman->state = DEAD;
					game.map[*x][*y].type = FANTOME;
				}
				else{
					game.map[*x][*y].type = FANTOME;
				}
			}
			break;
	}
}

/*
void initWALL(){
	for(int i=0;i<LENGTH;i++){
		for(int j=0;j<HEIGHT;j++){
			game.map[i][j].type = OBJECT;
			ILI9341_DrawFilledRectangle((uint16_t)((i)*10),(uint16_t)(j*10),(uint16_t)((i+1)*10),(uint16_t)((j+1)*10),ILI9341_COLOR_BLACK);
			//ILI9341_DrawPixel((uint16_t)((i*10)+5),(uint16_t)((j*10)+5),ILI9341_COLOR_WHITE);
		}
	}
	for(int i=0;i<HEIGHT;i++){
		game.map[0][i].type = WALL;
		ILI9341_DrawFilledRectangle((uint16_t)(310),(uint16_t)(i*10),(uint16_t)(320),(uint16_t)((i+1)*10),ILI9341_COLOR_BLUE);
	}
	for(int i=0;i<LENGTH;i++){
		game.map[i][HEIGHT-1].type = WALL;
		ILI9341_DrawFilledRectangle((uint16_t)(i*10),(uint16_t)(0),(uint16_t)((i+1)*10),(uint16_t)(10),ILI9341_COLOR_BLUE);
	}
	for(int i=0;i<LENGTH;i++){
		game.map[i][0].type = WALL;
		ILI9341_DrawFilledRectangle((uint16_t)(i*10),(uint16_t)(230),(uint16_t)((i+1)*10),(uint16_t)(240),ILI9341_COLOR_BLUE);
	}
	for(int i=0;i<HEIGHT;i++){
		game.map[LENGTH-1][i].type = WALL;
		ILI9341_DrawFilledRectangle((uint16_t)(0),(uint16_t)(i*10),(uint16_t)(10),(uint16_t)((i+1)*10),ILI9341_COLOR_BLUE);
	}
}*/

void initMAP(){
	for(int i=0;i<LENGTH;i++){				//point + contours
		for(int j=0;j<HEIGHT;j++){
			game.map[i][j].type = OBJECT;
			game.map[0][j].type = WALL;
			game.map[i][HEIGHT-1].type = WALL;
			game.map[i][0].type = WALL;
			game.map[LENGTH-1][j].type = WALL;
		}
	}

											//les murs
	for(int x=0;x<2;x++){					//carré
		for(int y=0;y<2;y++){
			game.map[15+x][11+y].type = WALL_WITH_PHANTOM;

			game.map[2+x][2+x].type = WALL;
			game.map[28+x][2+y].type = WALL;
			game.map[2+x][21+y].type = WALL;
			game.map[28+x][21+y].type = WALL;
			game.map[15+x][8+y].type = WALL;
			game.map[15+x][14+y].type = WALL;
		}
	}
	for(int y=7;y<17;y++){					//colonne de 10
		game.map[2][y].type = WALL;
		game.map[29][y].type = WALL;
	}
	for(int i=0;i<7;i++){					//longueur de 6
		game.map[i+13][2].type = WALL;
		game.map[i+13][29].type = WALL;

		game.map[13][i+4].type = WALL;
		game.map[13][i+14].type = WALL;
		game.map[18][i+4].type = WALL;
		game.map[18][i+14].type = WALL;

		game.map[8][i+9].type = WALL;
		game.map[23][i+9].type = WALL;
	}
	for(int i=0;i<4;i++){					//longueur de 4
		game.map[i+3][5].type = WALL;
		game.map[i+3][11].type = WALL;
		game.map[i+3][12].type = WALL;
		game.map[i+3][18].type = WALL;
		game.map[i+25][5].type = WALL;
		game.map[i+25][11].type = WALL;
		game.map[i+25][12].type = WALL;
		game.map[i+25][18].type = WALL;

		game.map[i+8][2].type = WALL;
		game.map[i+20][2].type = WALL;
		game.map[i+8][29].type = WALL;
		game.map[i+20][29].type = WALL;

		game.map[i+10][4].type = WALL;
		game.map[i+18][4].type = WALL;
		game.map[i+10][27].type = WALL;
		game.map[i+18][27].type = WALL;
	}
	for(int i=0;i<3;i++){					//longueur de 3
		game.map[5][i+1].type = WALL;
		game.map[6][i+1].type = WALL;
		game.map[25][i+1].type = WALL;
		game.map[26][i+1].type = WALL;

		game.map[5][i+28].type = WALL;
		game.map[6][i+28].type = WALL;
		game.map[25][i+28].type = WALL;
		game.map[26][i+28].type = WALL;

		game.map[8][i+3].type = WALL;
		game.map[23][i+3].type = WALL;
		game.map[8][i+18].type = WALL;
		game.map[23][i+18].type = WALL;

		game.map[15][i+4].type = WALL;
		game.map[16][i+4].type = WALL;
		game.map[15][i+17].type = WALL;
		game.map[16][i+17].type = WALL;

		game.map[12][i+8].type = WALL;
		game.map[18][i+8].type = WALL;
		game.map[12][i+13].type = WALL;
		game.map[18][i+13].type = WALL;

		game.map[4][i+7].type = WALL;
		game.map[6][i+7].type = WALL;
		game.map[25][i+7].type = WALL;
		game.map[27][i+7].type = WALL;
		game.map[4][i+14].type = WALL;
		game.map[6][i+14].type = WALL;
		game.map[25][i+14].type = WALL;
		game.map[27][i+14].type = WALL;
	}
	for(int i=0;i<2;i++){					//longueur de 2
		game.map[i+9][9].type = WALL;
		game.map[i+21][9].type = WALL;
		game.map[i+9][14].type = WALL;
		game.map[i+21][14].type = WALL;

		game.map[i+9][7].type = WALL;
		game.map[i+10][6].type = WALL;
		game.map[i+20][17].type = WALL;
		game.map[i+21][16].type = WALL;
		game.map[i+20][6].type = WALL;
		game.map[i+27][7].type = WALL;
		game.map[i+9][16].type = WALL;
		game.map[i+10][17].type = WALL;

		game.map[10][i+11].type = WALL;
		game.map[21][i+11].type = WALL;

		game.map[14][i+11].type = WALL;
		game.map[17][i+11].type = WALL;
	}
											//longueur de 1
	game.map[1][5].type = WALL;
	game.map[1][18].type = WALL;
	game.map[30][5].type = WALL;
	game.map[30][18].type = WALL;
	game.map[7][7].type = WALL;
	game.map[7][16].type = WALL;
	game.map[24][7].type = WALL;
	game.map[24][16].type = WALL;

	refreshMAP();
}

void refreshMAP(){
	for(int i=0;i<LENGTH;i++){
		for(int j=0;j<HEIGHT;j++){
			if(game.map[i][j].type == WALL || game.map[i][j].type == WALL_WITH_PHANTOM){
				ILI9341_DrawFilledRectangle((uint16_t)(i*10),(uint16_t)(j*10),(uint16_t)((i+1)*10),(uint16_t)((j+1)*10),ILI9341_COLOR_BLUE);
			}
			if(game.map[i][j].type == FREE){
				ILI9341_DrawFilledRectangle((uint16_t)(i*10),(uint16_t)(j*10),(uint16_t)((i+1)*10),(uint16_t)((j+1)*10),ILI9341_COLOR_BLACK);
			}
			if(game.map[i][j].type == OBJECT){
				ILI9341_DrawPixel((uint16_t)((i*10)+5),(uint16_t)((j*10)+5),ILI9341_COLOR_WHITE);
			}
		}
	}
}

bool getWALL(int x, int y){
	if(game.map[x][y].type == WALL || game.map[x][y].type == WALL_WITH_PHANTOM){
		return true;
	}else{
		return false;
	}
}
