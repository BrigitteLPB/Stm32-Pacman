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
#define	TIME_TO_UPDATE		350							// temps en ms avant une update du jeu

// global var
static volatile bool_e init = FALSE;
static volatile bool_e MS_FLAGS = FALSE;
//static volatile bool_e EVENT_COUNT = FALSE;

static volatile bool_e mur = FALSE;
static game_s game;

// private function
static void PRIVATE_LOGICAL_process_ms();

static void initMAP();
static bool_e getWALL(PACMAN_position pos);
static void sens_fantome(phantom_s *phantom);
static void mouvement(JOYSTICK_direction direction);
static void fantome_mvt();
static state_game VerifierEtatJeu();
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

void LOGICAL_init(bool_e hard){
	if(!init){
		Systick_add_callback_function(&PRIVATE_LOGICAL_process_ms);
		RAND_init();
		init = TRUE;
		initMAP();
		game.hard = hard;
	}

	RENDERER_init(&game);
}

void LOGICAL_kill(void){
	Systick_remove_callback_function(&PRIVATE_LOGICAL_process_ms);
	RENDERER_kill();
	init = FALSE;
}

state_game jeu(uint16_t *score){
	static JOYSTICK_direction dir = NEUTRE;

	dir = JOYSTICK_getDirection(JOYSTICK2);

	if(MS_FLAGS){
		mouvement(dir);
		fantome_mvt();
		RENDERER_show(&game);
	}

	RAND_catch_event();
	*score = game.pacman.score;
	return VerifierEtatJeu();
}

state_game VerifierEtatJeu(){
	if (game.pacman.state == DEAD){
		return MENU;
	}else if(game.pacman.score >= game.points_count){
		return WIN;
	}else{
		return JEU;
	}
}


void mouvement(JOYSTICK_direction direction){
	static PACMAN_position pos;
	pos = game.pacman.pos;

	switch(direction){
		case BAS:
			pos.y++;
			mur=getWALL(pos);
			pos.y--;
			if(mur==FALSE){
				game.map[pos.x][pos.y]= FREE;
				pos.y++;
			}
			break;
		case DROITE:
			pos.x++;
			mur=getWALL(pos);
			pos.x--;
			if(!mur){
				game.map[pos.x][pos.y] = FREE;
				pos.x++;
			}
			break;
		case GAUCHE:
			pos.x--;
			mur=getWALL(pos);
			pos.x++;
			if(!mur){
				game.map[pos.x][pos.y]  = FREE;
				pos.x--;
			}
			break;
		case HAUT:
			pos.y--;
			mur=getWALL(pos);
			pos.y++;
			if(!mur){
				game.map[pos.x][pos.y]  = FREE;
				pos.y--;
			}
			break;
		case NEUTRE:
			break;
	}

	if(game.map[pos.x][pos.y] == POINT){
		game.pacman.score++;
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
	}
}

void sens_fantome(phantom_s *phantom){
	PACMAN_position pos_copy = phantom->pos;
	bool_e first = TRUE;

	ghost_direction_e last_dir = G_NEUTRE;

//	bool_e murs[4] = {
//		getWALL((PACMAN_position){phantom->pos.x,(PACMAN_unit)(phantom->pos.y-1)}),		// haut
//		getWALL((PACMAN_position){phantom->pos.x,(PACMAN_unit)(phantom->pos.y+1)}),		// bas
//		getWALL((PACMAN_position){(PACMAN_unit)(phantom->pos.x +1), phantom->pos.y}),	// droite
//		getWALL((PACMAN_position){(PACMAN_unit)(phantom->pos.x-1),phantom->pos.y})		// gauche
//	};

	ghost_direction_e back_dir = G_NEUTRE;

	switch(phantom->direction){
		case HAUT:
			back_dir = G_BAS;
			break;
		case BAS:
			back_dir = G_HAUT;
			break;
		case DROITE:
			back_dir = G_GAUCHE;
			break;
		case GAUCHE:
			back_dir = G_DROITE;
			break;
		default:
			break;
	}

	bool_e mur_haut = getWALL((PACMAN_position){phantom->pos.x,(PACMAN_unit)(phantom->pos.y-1)});
	bool_e mur_bas = getWALL((PACMAN_position){phantom->pos.x,(PACMAN_unit)(phantom->pos.y+1)});
	bool_e mur_droit = getWALL((PACMAN_position){(PACMAN_unit)(phantom->pos.x +1), phantom->pos.y});
	bool_e mur_gauche = getWALL((PACMAN_position){(PACMAN_unit)(phantom->pos.x-1),phantom->pos.y});

	bool_e change_dir = FALSE;	// marque le changement de direction

	do{
		switch(phantom->direction){
			case G_HAUT:			//haut
				if(!mur_haut && ((mur_gauche && mur_droit) || change_dir) && back_dir != phantom->direction){
					phantom->pos.y--;
				}else{
					last_dir = phantom->direction;
					phantom->direction = G_NEUTRE;
				}
				break;
			case G_BAS :		//bas
				if(!mur_bas && ((mur_gauche && mur_droit) || change_dir) && back_dir != phantom->direction){
					phantom->pos.y++;
				}else{
					last_dir = phantom->direction;
					phantom->direction = G_NEUTRE;
				}
				break;
			case G_DROITE:		//droite
				if(!mur_droit && ((mur_bas && mur_haut) || change_dir) && back_dir != phantom->direction){
					phantom->pos.x++;
				}else{
					last_dir = phantom->direction;
					phantom->direction = G_NEUTRE;
				}
				break;

			case G_GAUCHE:		//gauche
				if(!mur_gauche && ((mur_bas && mur_haut) || change_dir) && back_dir != phantom->direction){
					phantom->pos.x--;
				}else{
					last_dir = phantom->direction;
					phantom->direction = G_NEUTRE;
				}
				break;
			case G_NEUTRE:
				change_dir = TRUE;
				if(first){
					phantom->direction = (ghost_direction_e)(RAND_get()%4);
					first = FALSE;
				}else{
					phantom->direction = (ghost_direction_e)((last_dir+1)%4);
				}
				break;
		}
	}while(phantom->pos.x == pos_copy.x && phantom->pos.y == pos_copy.y);

	if(game.pacman.pos.x == phantom->pos.x && game.pacman.pos.y == phantom->pos.y){
		game.pacman.state = DEAD;
	}
}

void initMAP(){
	game.points_count = 379;				// nombre de point sur le terrain

	for(int i=0;i<LENGTH;i++){				//point + contours
		for(int j=0;j<HEIGHT;j++){
			game.map[i][j] = POINT;
			game.map[0][j] = WALL;
			game.map[i][HEIGHT-1] = WALL;
			game.map[i][0] = WALL;
			game.map[LENGTH-1][j] = WALL;
		}
	}

	// pacman
	game.pacman.score = 0;
	game.pacman.state = ALIVE;
	game.pacman.pos.y = 1;
	game.pacman.pos.x = 1;
	game.map[game.pacman.pos.x][game.pacman.pos.y] = PACMAN;


	game.phantom_count = 4;
	uint8_t phantom_count = 0;				//les murs
	for(int x=0;x<2;x++){					//carre
		for(int y=0;y<2;y++){
			// phantoms
			game.map[15+x][11+y] = WALL_WITH_PHANTOM;
			game.phantoms[phantom_count].pos.x = (PACMAN_unit)(15+x);
			game.phantoms[phantom_count].pos.y = (PACMAN_unit)(11+y);
			game.phantoms[phantom_count].direction = NEUTRE;
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

bool_e getWALL(PACMAN_position pos){
	return game.map[pos.x][pos.y] == WALL || game.map[pos.x][pos.y] == WALL_WITH_PHANTOM;
}
