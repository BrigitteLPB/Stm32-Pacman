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
		OBJECT,	//cell with a point on it
		PACMAN,
		FANTOME
	}cell_s;

	// object / caracter

	typedef struct {
		void* data;
	}object_s;

// ojects
	// pacman
	typedef enum{
		ALIVE,
		DEAD,
		PREDATOR		//under gumball effect
	}type_state_pacman;

	typedef struct {
		PACMAN_position pos;
		uint8_t score;
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
		uint8_t points_count;	// 0 -> win
		cell_s map[LENGTH][HEIGHT];
		phantom_s phantoms[MAX_PHANTOM];
		pacman_s pacman;
	}game_s;


	// functions




#endif /* LOGICAL_TYPE_H_ */
