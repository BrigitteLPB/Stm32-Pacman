
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
#define CASE_HEIGHT	TFT_WIDTH/HEIGHT		// swaping height and width due to the landscape orientation
#define CASE_WIDTH	TFT_HEIGHT/LENGTH

typedef struct{
	TFT_color_e colors[4];
	TFT_image_s img;
}PRIVATE_img_ghosts_s;


// global
	// every images for the game
static TFT_object_s wall;
static TFT_object_s ground;
static PRIVATE_img_ghosts_s ghosts;
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
//	TFT_color_e colors[4] = {COLOR_RED, COLOR_MAGENTA, COLOR_CYAN, COLOR_ORANGE};

	ghosts.img.begin = TFT_make_image((pos_s){0,0}, CASE_HEIGHT, CASE_WIDTH);
	ghosts.colors[0] = COLOR_RED;
	ghosts.colors[1] = COLOR_MAGENTA;
	ghosts.colors[2] = COLOR_CYAN;
	ghosts.colors[3] = COLOR_ORANGE;

	if(ghosts.img.begin != NULL){

	}

//	(TFT_color_e[CASE_HEIGHT][CASE_WIDTH]){
//		{COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE},
//		{COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE},
//		{COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE},
//		{COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE},
//		{COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE},
//		{COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE},
//		{COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE},
//		{COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE},
//		{COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE},
//		{COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE}
//	};

	for(int i=0; i<4; i++){

	}
}

void PRIVATE_RENDERER_init_pacman(){
	TFT_init_object(&pacman);

	pacman.color = COLOR_YELLOW;
	pacman.filled = TRUE;
//	pacman.
}

void RENDERER_test(){
	TFT_put_image_swap_color(&ghosts.img, ghosts.colors[0], ghosts.colors[0]);
}
