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


}

bool getWALL(int x, int y){
	if(game.map[x][y].type == WALL || game.map[x][y].type == WALL_WITH_PHANTOM){
		return true;
	}else{
		return false;
	}
}
