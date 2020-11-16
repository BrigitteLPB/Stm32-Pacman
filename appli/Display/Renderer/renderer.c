
/**
 * @file	game_renderer.c
 * @brief	all definition to render the game
 * @author	Th�o Guillemaud
 */
#include "renderer.h"
// include
#include "../../Abstract/TFT/TFT_basic.h"
#include "../../Abstract/TFT/TFT_advanced.h"
#include "../../Abstract/TFT/TFT_image_alloc.h"

#include "../../Logical/type.h"


// const
#define CASE_HEIGHT	TFT_WIDTH/HEIGHT		// swaping height and width due to the landscape orientation
#define CASE_WIDTH	TFT_HEIGHT/LENGTH

typedef struct{
	TFT_color_e colors[4];
	TFT_image_s img;
}PRIVATE_img_ghosts_s;

typedef enum {
	GHOST_1 = 0,
	GHOST_2 = 1,
	GHOST_3 = 2,
	GHOST_4 = 3
}RENDERER_ghost_e;


// global
	// every images for the game
static TFT_object_s wall;
static TFT_object_s ground;
static PRIVATE_img_ghosts_s ghosts;
static TFT_image_s pacman;


static game_s game_copy;


// private prototype
static void PRIVATE_RENDERER_init_wall();

static void PRIVATE_RENDERER_init_ground();

static void PRIVATE_RENDERER_init_ghosts();

static void PRIVATE_RENDERER_init_pacman();

/**
 * @param	pos	game position
 */
static void PRIVATE_RENDERER_put_wall(pos_s pos);

/**
 * @param	pos	game position
 */
static void PRIVATE_RENDERER_put_ground(pos_s pos);

/**
 * @param	pos	game position
 */
static void PRIVATE_RENDERER_put_ghost(pos_s pos, RENDERER_ghost_e ghost_chose);

/**
 * @param	pos	game position
 */
static void PRIVATE_RENDERER_put_pacman(pos_s pos);

// function
void RENDERER_init(void){
	PRIVATE_RENDERER_init_wall();
	PRIVATE_RENDERER_init_ground();
	PRIVATE_RENDERER_init_ghosts();
	PRIVATE_RENDERER_init_pacman();
}

void RENDERER_kill(void){
	IMG_ALLOC_delete(ghosts.img.begin);
	IMG_ALLOC_delete(pacman.begin);
}

void RENDERER_reset(void){
	RENDERER_kill();
	RENDERER_init();
}

void RENDERER_show(game_s *game){
	for(int y=0; y<LENGTH;y++){
		for(int x=0; x<HEIGHT; x++){
			if(game->map[y][x] != game_copy.map[y][x]){
				pos_s pos;
				pos.y = y;
				pos.x = x;

				switch(game->map[y][x]){
					case WALL:
					case WALL_WITH_PHANTOM:
						PRIVATE_RENDERER_put_wall(pos);
						break;
					case FREE:
						PRIVATE_RENDERER_put_ground(pos);
						break;
					case OBJECT:
						break;
				}
			}
		}
	}

	// show fantome and pacman
	for(int i=0; i<game->phantom_count; i++){
		PRIVATE_RENDERER_put_ghost(game->phantoms[i].pos, (RENDERER_ghost_e)i);
	}

	PRIVATE_RENDERER_put_pacman(game->pacman.pos);

	game_copy = game;
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
	ghosts.img = TFT_make_image((pos_s){0,0}, CASE_HEIGHT, CASE_WIDTH);
	ghosts.colors[0] = COLOR_RED;
	ghosts.colors[1] = COLOR_MAGENTA;
	ghosts.colors[2] = COLOR_CYAN;
	ghosts.colors[3] = COLOR_ORANGE;

	TFT_color_e datas[] = {
		COLOR_NONE, COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE,
		COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE,
		ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, ghosts.colors[0], ghosts.colors[0], COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0],
		ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0],
		ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0],
		ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0],
		ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0],
		ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], ghosts.colors[0],
		ghosts.colors[0], ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, ghosts.colors[0], ghosts.colors[0], ghosts.colors[0],
		ghosts.colors[0], ghosts.colors[0], COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE, ghosts.colors[0], ghosts.colors[0]
	};

	TFT_fill_image(&ghosts.img, datas);
}

void PRIVATE_RENDERER_init_pacman(){
	pacman = TFT_make_image((pos_s){0,0}, CASE_HEIGHT, CASE_WIDTH);

	TFT_color_e datas[] = {
		COLOR_NONE,		COLOR_NONE,		COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_NONE,		COLOR_NONE,
		COLOR_NONE,		COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_NONE,
		COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_NONE, 	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,
		COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_NONE,		COLOR_NONE,
		COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,
		COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,
		COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_NONE,		COLOR_NONE,
		COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,
		COLOR_NONE, 	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_NONE,
		COLOR_NONE, 	COLOR_NONE, 	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_YELLOW,	COLOR_NONE,		COLOR_NONE
	};

	TFT_fill_image(&pacman, datas);
}

void PRIVATE_RENDERER_put_wall(pos_s pos){
	uint16_t x = pos.x*CASE_WIDTH;
	uint16_t y = pos.y*CASE_HEIGHT;

	TFT_move_object(&wall, x, y);
	TFT_draw_object(&wall);

	TFT_move_object(&wall, -x, -y);
}

void PRIVATE_RENDERER_put_ground(pos_s pos){
	uint16_t x = pos.x*CASE_WIDTH;
	uint16_t y = pos.y*CASE_HEIGHT;

	TFT_move_object(&ground, x, y);
	TFT_draw_object(&ground);

	TFT_move_object(&ground, -x, -y);
}

void PRIVATE_RENDERER_put_ghost(pos_s pos, RENDERER_ghost_e ghost_chose){
	ghosts.img.position.x = (position) (pos.x * CASE_WIDTH);
	ghosts.img.position.y = (position)(pos.y * CASE_HEIGHT);

	TFT_put_image_swap_color(&ghosts.img, ghosts.colors[0], ghosts.colors[(uint8_t) ghost_chose]);
	ghosts.img.position = (pos_s){0,0};
}

void PRIVATE_RENDERER_put_pacman(pos_s pos){
	pacman.position.x = (position) (pos.x * CASE_WIDTH);
	pacman.position.y = (position)(pos.y * CASE_HEIGHT);

	TFT_put_image(&pacman);
	ghosts.img.position = (pos_s){0,0};
}

void RENDERER_test(){
//	for(int i=0; i<6; i++){
//		PRIVATE_RENDERER_put_ground((pos_s){0,i});
//	}
//
//	PRIVATE_RENDERER_put_ghost((pos_s){0,0}, GHOST_1);
//	PRIVATE_RENDERER_put_ghost((pos_s){0,1}, GHOST_2);
//	PRIVATE_RENDERER_put_ghost((pos_s){0,2}, GHOST_3);
//	PRIVATE_RENDERER_put_ghost((pos_s){0,3}, GHOST_4);
//	PRIVATE_RENDERER_put_pacman((pos_s){0,4});
//	PRIVATE_RENDERER_put_wall((pos_s){0,5});

	game_s game;
	game.phantom_count = 4;
	game.phantoms[0].pos = (pos_s){1,0};
	game.phantoms[1].pos = (pos_s){3,3};
	game.phantoms[2].pos = (pos_s){3,6};
	game.phantoms[3].pos = (pos_s){3,9};
	game.pacman.pos = (pos_s){3,12};

	for(int y=0; y<LENGTH; y++){
		for(int x=0; x<HEIGHT; x++){
			if(y==0 || y<LENGTH-1 || x==0 || x==HEIGHT-1){
				game.map[y][x] = WALL;
			}else{
				game.map[y][x] = FREE;
			}
		}
	}

	RENDERER_show(&game);
}
