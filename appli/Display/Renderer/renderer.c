/**
 * @file	game_renderer.c
 * @brief	all definition to render the game
 * @author	Théo Guillemaud
 */
#include "renderer.h"
// include
#include "../../Abstract/TFT/TFT_basic.h"
#include "../../Abstract/TFT/TFT_advanced.h"

#include "../../Logical/type.h"


// const
#define CASE_HEIGHT	TFT_HEIGHT/HEIGHT
#define CASE_WIDTH	TFT_WIDTH/LENGTH


// global
	// every images for the game
static TFT_object_s wall;
static TFT_object_s ground;
static TFT_object_s ghosts[4];
static TFT_object_s pacman;




// private prototype
static void PRIVATE_RENDERER_init_wall();

static void PRIVATE_RENDERER_init_ground();

static void PRIVATE_RENDERER_init_ghosts();

static void PRIVATE_RENDERER_init_pacman();

// function
void RENDERER_init(void){
	PRIVATE_RENDERER_init_wall();
	PRIVATE_RENDERER_init_ground();
	PRIVATE_RENDERER_init_ghosts();
}

void RENDERER_kill(void){

}

void RENDERER_reset(void){

}

void PRIVATE_RENDERER_init_wall(){
	pos_s bottom_rigth;
	bottom_rigth.y = CASE_HEIGHT-1;
	bottom_rigth.x = CASE_WIDTH-1;

	wall = TFT_make_rect((pos_s){0, 0}, bottom_rigth, COLOR_BLUE, TRUE);
}

void PRIVATE_RENDERER_init_ground(){
	pos_s bottom_rigth;
	bottom_rigth.y = CASE_HEIGHT-1;
	bottom_rigth.x = CASE_WIDTH-1;

	ground = TFT_make_rect((pos_s){0,0}, bottom_rigth, COLOR_BLACK, TRUE);
}

void PRIVATE_RENDERER_init_ghosts(){
	TFT_color_e colors[4] = {COLOR_RED, COLOR_MAGENTA, COLOR_CYAN, COLOR_ORANGE};

	for(int i=0; i<4; i++){
		TFT_init_object(&ghosts[i]);
		ghosts[i].color = colors[i];
		ghosts[i].filled= TRUE;
		ghosts[i].nb_points = 8;

		ghosts[i].points[0] = (pos_s){1,6};
		ghosts[i].points[1] = (pos_s){2,8};
		ghosts[i].points[2] = (pos_s){8,8};
		ghosts[i].points[3] = (pos_s){7,5};
		ghosts[i].points[4] = (pos_s){7,4};
		ghosts[i].points[5] = (pos_s){8,1};
		ghosts[i].points[6] = (pos_s){2,1};
		ghosts[i].points[7] = (pos_s){1,3};
	}
}

void PRIVATE_RENDERER_init_pacman(){
	TFT_init_object(&pacman);

	pacman.color = COLOR_YELLOW;
	pacman.filled = TRUE;
	pacman.
}

void RENDERER_test(){
	TFT_draw_object(&ghosts[0]);
}
