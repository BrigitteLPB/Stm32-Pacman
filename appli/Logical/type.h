/*
 * type.h
 *
 *  Created on: 6 Oct 2020
 *      Author: Théo Malinge--Lecompte
 */

#ifndef LOGICAL_TYPE_H_
#define LOGICAL_TYPE_H_

	// include
	#include "stdbool.h"
	#include "macro_types.h"

//IA state
	#define LENGTH 32	// largeur de la map
	#define	HEIGHT 24	// hauteur de la map

	#define MAX_PHANTOM	4	// maximum on the map

	typedef uint8_t PACMAN_unit;

	typedef  struct{
		PACMAN_unit x;
		PACMAN_unit y;
	}PACMAN_position;

//state cell
	// cell
	typedef enum{
		WALL,		//cell where we have a wall
		WALL_WITH_PHANTOM,	// phantom spawn area
		FREE,		//cell with nothing on it
		FRUIT,	//cell with a point on it
		FANTOME_WITH_FRUIT,
		POINT,
		FANTOME_WITH_POINT,
		PACMAN,
		FANTOME
	}cell_s;


	// pacman
	typedef enum{
		ALIVE,
		DEAD,
		PREDATOR		//under gumball effect
	}type_state_pacman;

	typedef struct {
		PACMAN_position pos;
		uint16_t score;
		type_state_pacman state;
	}pacman_s;

	// phantom
	typedef enum{
		LIBERATE,
		CAPTIVE,
		PREY			//under gumball effect
	}type_state_PHANTOM;	

	typedef struct {
		PACMAN_position pos;
		type_state_PHANTOM state;
		int8_t timer;		// 0: move, -1: stay, >0: wait for moving
	}phantom_s;


// map
	typedef struct{
		uint8_t phantom_count;
		uint16_t points_count;
		cell_s map[LENGTH][HEIGHT];
		phantom_s phantoms[MAX_PHANTOM];
		pacman_s pacman;
	}game_s;

	typedef enum{
		INIT,
		JEU,
		//GAME_OVER,
		WIN,
		MENU
	}state_game;

	// functions




#endif /* LOGICAL_TYPE_H_ */
