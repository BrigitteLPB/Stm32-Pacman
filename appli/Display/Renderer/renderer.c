
/**
 * @file	game_renderer.c
 * @brief	all definition to render the game
 * @author	Th�o Guillemaud
 */
#include "renderer.h"
// include
#include "macro_types.h"
#include "../../Abstract/TFT/TFT_basic.h"
#include "../../Abstract/TFT/TFT_advanced.h"
#include "../../Abstract/TFT/TFT_image_alloc.h"

#include "../../Abstract/Button/button.h"
#include "../../Abstract/Rand/rand.h"

// const
#define CASE_HEIGHT	TFT_WIDTH/HEIGHT		// swaping height and width due to the landscape orientation
#define CASE_WIDTH	TFT_HEIGHT/LENGTH

typedef enum {
	GHOST_1,
	GHOST_2,
	GHOST_3,
	GHOST_4
}RENDERER_ghost_e;

typedef struct{
	TFT_color_e colors[4];
	TFT_image_s img;
}PRIVATE_img_ghosts_s;


// global
static volatile bool_e init = FALSE;

	// every images for the game
static TFT_object_s wall;
static TFT_object_s ground;
static PRIVATE_img_ghosts_s ghosts;
static TFT_image_s pacman;
static TFT_object_s point;
static TFT_image_s fruit;

static game_s game_copy;


// private prototype
static void PRIVATE_RENDERER_init_wall();

static void PRIVATE_RENDERER_init_ground();

static void PRIVATE_RENDERER_init_ghosts();

static void PRIVATE_RENDERER_init_pacman();

static void PRIVATE_RENDERER_init_point();

static void PRIVATE_RENDERER_init_fruit();

static void PRIVATE_RENDERER_put_point(PACMAN_position pos);

static void PRIVATE_RENDERER_put_fruit(PACMAN_position pos);

static void PRIVATE_RENDERER_show(game_s* game, bool_e fullPrint);

//static bool_e PRIVATE_RENDERER_anti_ghosting(PACMAN_unit x, PACMAN_unit y, game_s *game, game_s *game_copy);

//static void PRIVATE_RENDERER_clear_ghosting(game_s *game);

static void PRIVATE_RENDERER_show_pac_ghost(game_s *game);

static void PRIVATE_RENDERER_put(PACMAN_position pos, cell_s type);

/**
 * @param	pos	game position
 */
static void PRIVATE_RENDERER_put_wall(PACMAN_position pos);

/**
 * @param	pos	game position
 */
static void PRIVATE_RENDERER_put_ground(PACMAN_position pos);

/**
 * @param	pos	game position
 */
static void PRIVATE_RENDERER_put_ghost(PACMAN_position pos, RENDERER_ghost_e ghost_chose);

/**
 * @param	pos	game position
 */
static void PRIVATE_RENDERER_put_pacman(PACMAN_position pos, bool_e predator);


// function
void RENDERER_init(game_s *game){
	if(!init){
		PRIVATE_RENDERER_init_wall();
		PRIVATE_RENDERER_init_ground();
		PRIVATE_RENDERER_init_ghosts();
		PRIVATE_RENDERER_init_pacman();
		PRIVATE_RENDERER_init_point();
		PRIVATE_RENDERER_init_fruit();

		init = TRUE;
	}

	game_copy = *game;
	PRIVATE_RENDERER_show(game, TRUE);
}

void RENDERER_kill(void){
//	IMG_ALLOC_delete(ghosts.img.begin);
//	IMG_ALLOC_delete(pacman.begin);
//	init = FALSE;
}

void RENDERER_reset(game_s *game){
	RENDERER_kill();
	RENDERER_init(game);
}

void RENDERER_show(game_s *game){
	PRIVATE_RENDERER_show(game, FALSE);
}

void PRIVATE_RENDERER_show(game_s* game, bool_e fullPrint){
	// show fantomes and pacman avant pour eviter le cliping
	if(!fullPrint){
		PRIVATE_RENDERER_show_pac_ghost(game);
	}

	// show the map
	for(PACMAN_unit x=0; x<LENGTH; x++){
		for(PACMAN_unit y=0; y<HEIGHT; y++){
			if(game->map[x][y] != game_copy.map[x][y] || fullPrint){
				PACMAN_position pos;
				pos.y = (PACMAN_unit) y;
				pos.x = (PACMAN_unit) x;

				PRIVATE_RENDERER_put(pos, game->map[x][y]);
			}
		}
	}

	if(fullPrint){
		PRIVATE_RENDERER_show_pac_ghost(game);
	}

//	PRIVATE_RENDERER_clear_ghosting(game);

	game_copy = *game;
}

void PRIVATE_RENDERER_show_pac_ghost(game_s *game){
	for(uint8_t i=0; i<game->phantom_count; i++){
//		switch(game->map[game->phantoms[i].pos.x][game->phantoms[i].pos.y]){
//			case FRUIT:
//			case POINT:
//			case FREE:
//				PRIVATE_RENDERER_put_ground(game->phantoms[i].pos);
//				break;
//			default:
//				break;
//
//		}
		PRIVATE_RENDERER_put_ghost(game->phantoms[i].pos, (RENDERER_ghost_e)i);
	}

//	PRIVATE_RENDERER_put_ground(game->pacman.pos);
	if(game->pacman.state == PREDATOR){
		PRIVATE_RENDERER_put_pacman(game->pacman.pos, TRUE);
	}else{
		PRIVATE_RENDERER_put_pacman(game->pacman.pos, FALSE);
	}
}

//bool_e PRIVATE_RENDERER_anti_ghosting(PACMAN_unit x, PACMAN_unit y, game_s *game, game_s *game_copy){
//	if(x == game->pacman.pos.x && y == game->pacman.pos.y && x != game_copy->pacman.pos.x && y != game_copy->pacman.pos.y){
//		return TRUE;
//	}else{
//		for(uint8_t i=0; i<game->phantom_count; i++){
////			if(x == game->phantoms[i].pos.x && y == game->phantoms[i].pos.y && game->phantoms[i].pos.x != game_copy->phantoms[i].pos.x && game->phantoms[i].pos.y != game_copy->phantoms[i].pos.y){
//			if(x == game_copy->phantoms[i].pos.x && y == game_copy->phantoms[i].pos.y){
//				return TRUE;
//			}
//		}
//		return FALSE;
//	}
//}

//void PRIVATE_RENDERER_clear_ghosting(game_s *game){
//	PACMAN_position positions[5] = {game_copy.pacman.pos, game_copy.phantoms[0].pos, game_copy.phantoms[1].pos, game_copy.phantoms[2].pos, game_copy.phantoms[3].pos};
//
//	for(uint8_t i=0; i<game->phantom_count+1; i++){
//		bool_e update = FALSE;
//
//		update = (positions[i].x == game->pacman.pos.x && positions[i].y == game->pacman.pos.y);
//
//		for(uint8_t j=0; j<game->phantom_count; j++){
//			if(positions[i].x == game->phantoms[j].pos.x && positions[i].y == game->phantoms[j].pos.y){
//				update = TRUE;
//			}
//		}
//
//		if(update){
//			PRIVATE_RENDERER_put(positions[i], game->map[positions[i].x][positions[i].y]);
//		}
//	}
//}

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

void PRIVATE_RENDERER_init_point(){
	point = TFT_make_rect((pos_s){(position)(CASE_HEIGHT/2 -1), (position)(CASE_WIDTH/2 -1)}, (pos_s){(position)(CASE_HEIGHT/2), (position)(CASE_WIDTH/2)}, COLOR_WHITE, TRUE);
}

void PRIVATE_RENDERER_init_fruit(){
	fruit = TFT_make_image((pos_s){0,0}, CASE_HEIGHT, CASE_WIDTH);

	TFT_color_e datas[] = {
		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_GREEN,	COLOR_GREEN,	COLOR_NONE,
		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_GREEN,	COLOR_NONE,		COLOR_NONE,		COLOR_NONE,
		COLOR_NONE,		COLOR_NONE,		COLOR_RED,		COLOR_RED, 		COLOR_NONE,		COLOR_GREEN,	COLOR_RED,		COLOR_RED,		COLOR_NONE,		COLOR_NONE,
		COLOR_NONE,		COLOR_NONE,		COLOR_RED,		COLOR_RED, 		COLOR_RED,		COLOR_RED,		COLOR_RED,		COLOR_RED,		COLOR_NONE,		COLOR_NONE,
		COLOR_NONE,		COLOR_NONE,		COLOR_RED,		COLOR_RED, 		COLOR_RED,		COLOR_RED,		COLOR_RED,		COLOR_RED,		COLOR_NONE,		COLOR_NONE,
		COLOR_NONE,		COLOR_NONE,		COLOR_RED,		COLOR_RED, 		COLOR_RED,		COLOR_RED,		COLOR_RED,		COLOR_RED,		COLOR_NONE,		COLOR_NONE,
		COLOR_NONE,		COLOR_NONE,		COLOR_RED,		COLOR_RED, 		COLOR_RED,		COLOR_RED,		COLOR_RED,		COLOR_RED,		COLOR_NONE,		COLOR_NONE,
		COLOR_NONE,		COLOR_NONE,		COLOR_RED,		COLOR_RED, 		COLOR_RED,		COLOR_RED,		COLOR_RED,		COLOR_RED,		COLOR_NONE,		COLOR_NONE,
		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,
		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE,		COLOR_NONE
	};

	TFT_fill_image(&fruit, datas);

}

void PRIVATE_RENDERER_put(PACMAN_position pos, cell_s type){
	switch (type) {
		case WALL:
		case WALL_WITH_PHANTOM:
			PRIVATE_RENDERER_put_wall(pos);
			break;
		case FREE:
//		case PACMAN:
//		case FANTOME:
//		case FANTOME_WITH_FRUIT:
//		case FANTOME_WITH_POINT:
			PRIVATE_RENDERER_put_ground(pos);
			break;
		case FRUIT:
			PRIVATE_RENDERER_put_fruit(pos);
			break;
		case POINT:
			PRIVATE_RENDERER_put_ground(pos);
			PRIVATE_RENDERER_put_point(pos);
			break;
		default:
			break;
	}
}

void PRIVATE_RENDERER_put_wall(PACMAN_position pos){
	uint16_t x = (uint16_t) (pos.x*CASE_WIDTH);
	uint16_t y = (uint16_t) (pos.y*CASE_HEIGHT);

	TFT_move_object(&wall, (position)x, (position)y);
	TFT_draw_object(&wall);

	TFT_move_object(&wall, (position)-x, (position)-y);
}

void PRIVATE_RENDERER_put_ground(PACMAN_position pos){
	uint16_t x = (uint16_t)(pos.x*CASE_WIDTH);
	uint16_t y = (uint16_t)(pos.y*CASE_HEIGHT);

	TFT_move_object(&ground, (position)x, (position)y);
	TFT_draw_object(&ground);

	TFT_move_object(&ground, (position)-x, (position)-y);
}

void PRIVATE_RENDERER_put_ghost(PACMAN_position pos, RENDERER_ghost_e ghost_chose){
	ghosts.img.position.x = (position) (pos.x * CASE_WIDTH);
	ghosts.img.position.y = (position)(pos.y * CASE_HEIGHT);

	TFT_put_image_swap_color(&ghosts.img, ghosts.colors[0], ghosts.colors[(uint8_t) ghost_chose]);
	ghosts.img.position = (pos_s){0,0};
}

void PRIVATE_RENDERER_put_pacman(PACMAN_position pos, bool_e predator){
	pacman.position.x = (position) (pos.x * CASE_WIDTH);
	pacman.position.y = (position)(pos.y * CASE_HEIGHT);

	if(predator){
		TFT_put_image_swap_color(&pacman, COLOR_YELLOW, COLOR_BLUE);
	}else{
		TFT_put_image(&pacman);
	}

	pacman.position = (pos_s){0,0};
}

void PRIVATE_RENDERER_put_point(PACMAN_position pos){
	uint16_t x = (uint16_t)(pos.x*CASE_WIDTH);
	uint16_t y = (uint16_t)(pos.y*CASE_HEIGHT);

	TFT_move_object(&point, (position)x, (position)y);
	TFT_draw_object(&point);

	TFT_move_object(&point, (position)-x, (position)-y);
}

void PRIVATE_RENDERER_put_fruit(PACMAN_position pos){
	fruit.position.x = (position) (pos.x * CASE_WIDTH);
	fruit.position.y = (position)(pos.y * CASE_HEIGHT);

	TFT_put_image(&fruit);

	fruit.position = (pos_s){0,0};
}

void RENDERER_test(){
	game_s game;
	game.phantom_count = 4;
	for(int x=0; x<LENGTH; x++){
		for(int y=0; y<HEIGHT; y++){
			if(y==0 || y==HEIGHT-1 || x==0 || x==LENGTH-1){
				game.map[x][y] = WALL;
			}else{
				game.map[x][y] = FREE;
			}
		}
	}

	game.pacman.pos = (PACMAN_position){1,1};
	game.map[game.pacman.pos.x][game.pacman.pos.y] = PACMAN;

	for(int i=0; i<game.phantom_count; i++){
		game.phantoms[i].pos = (PACMAN_position){(PACMAN_unit)(i+1),2};
		game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y] = FANTOME;
	}

	RENDERER_init(&game);
	BUTTON_init();
	RAND_init();

	// change the game
	while(TRUE){
		// pacman
		game.map[game.pacman.pos.x][game.pacman.pos.y] = FREE;
		game.pacman.pos = (PACMAN_position){(PACMAN_unit)((RAND_get()%(LENGTH-2)+1)),(PACMAN_unit)((RAND_get()%(HEIGHT-2))+1)};
		game.map[game.pacman.pos.x][game.pacman.pos.y] = PACMAN;

		// phantom
		for(int i=0; i<game.phantom_count; i++){
			game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y] = FREE;
			game.phantoms[i].pos = (PACMAN_position){(PACMAN_unit)((RAND_get()%(LENGTH-2)+1)),(PACMAN_unit)((RAND_get()%(HEIGHT-2))+1)};
			game.map[game.phantoms[i].pos.x][game.phantoms[i].pos.y] = FANTOME;
		}

		// a wall
		game.map[(RAND_get()%(LENGTH-2))+1][(RAND_get()%(HEIGHT-2))+1] = WALL;

		// a ground
		game.map[(RAND_get()%(LENGTH-2))+1][(RAND_get()%(HEIGHT-2))+1] = FREE;

		// a fruit
		game.map[(RAND_get()%(LENGTH-2))+1][(RAND_get()%(HEIGHT-2))+1] = FRUIT;

		// a point
		game.map[(RAND_get()%(LENGTH-2))+1][(RAND_get()%(HEIGHT-2))+1] = POINT;

		// show
		RENDERER_show(&game);

		// block input
		while(BUTTON_state_machine() == BUTTON_EVENT_NONE){
			RAND_catch_event();
		}
	}
}

