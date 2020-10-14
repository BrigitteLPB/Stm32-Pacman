/*
 * Logical.c
 *
 *  Created on: 13 Oct 2020
 *      Author: Théo Malinge--Lecompte
 */
#include"Logical/Logical.h"
#include "Abstract/Joystick/joystick.h"
#include "stdbool.h"

volatile static bool mur = false;
static game_s game;

static bool getWALL(int x, int y);


void mouvement(JOYSTICK_direction direction){
	static uint16_t x=10;
	static uint16_t y=10;
	static uint16_t s=10;
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
			}
			break;
		case GAUCHE:
			x++;
			mur=getWALL(x,y);
			x--;
			if(mur==false){
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_BLACK);
				game.map[x][y].type = FREE;
				x++;
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
			}
			break;
		case DROITE:
			x--;
			mur=getWALL(x,y);
			x++;
			if(mur==false){
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_BLACK);
				game.map[x][y].type = FREE;
				x--;
				ILI9341_DrawFilledRectangle((uint16_t)(x*s),(uint16_t)(y*s),(uint16_t)((x+1)*s),(uint16_t)((y+1)*s),ILI9341_COLOR_YELLOW);
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
			}
			break;
		case NEUTRE:
			break;
	}
}

void initWALL(){
	for(int i=0;i<LENGTH;i++){
		for(int j=0;j<HEIGHT;j++){
			game.map[i][j].type = POINT;
			ILI9341_DrawFilledRectangle((uint16_t)((i)*10),(uint16_t)(j*10),(uint16_t)((i+1)*10),(uint16_t)((j+1)*10),ILI9341_COLOR_BLACK);
			ILI9341_DrawPixel((uint16_t)((i*10)+5),(uint16_t)((j*10)+5),ILI9341_COLOR_WHITE);
		}
	}
	for(int i=0;i<LENGTH;i++){
		game.map[i][HEIGHT].type = WALL;
		ILI9341_DrawFilledRectangle((uint16_t)(i*10),(uint16_t)(0),(uint16_t)((i+1)*10),(uint16_t)(10),ILI9341_COLOR_BLUE);
	}

}

bool getWALL(int x, int y){
	if(game.map[x][y].type == WALL || game.map[x][y].type == WALL_WITH_PHANTOM){
		return true;
	}else{
		return false;
	}
}
