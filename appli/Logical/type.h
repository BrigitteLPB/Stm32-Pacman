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

//IA state
#define LENGTH 320
#define HEIGHT 240

	typedef enum{
		ALIVE,
		DEAD,
		PREDATOR		//under gumball effect
	}type_state_pacman;

	typedef enum{
		LIBERATE,
		CAPTIVE,
		PREY			//under gumball effect
	}type_state_FANTOME;

	typedef struct{
		type_state_pacman pacman;
		type_state_FANTOME fantome;
	}IA_state;

//state cell
	typedef enum{
		WALL,		//cell where we have a wall
		FREE,		//cell with nothing on it
		OBJECT		//cell with a point on it
	}type_cell;

	typedef enum{		//OBJECT
		PACMAN,
		FANTOME,
		GUMBALL,
		CHERRY,
		POINT
	}type_object;

	typedef struct {
		void *cell;
		type_cell square;
		type_object object;
	}cell_s;

	typedef struct{
		IA_state ia;
		cell_s display;
		int Length[LENGTH];
		int Heigth[HEIGHT];
	}game_s;








	// functions




#endif /* LOGICAL_TYPE_H_ */
