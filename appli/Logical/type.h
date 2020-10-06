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
	#include "joystick.h"


	// const
	#define ALIVE true

	typedef enum{
		WALL,		//cell where we have a wall
		FREE,		//cell with nothing on it
		OBJECT		//cell with a point on it
	}type_cell;

	typedef enum{
		PACMAN,
		FANTOME,
		GUMBALL,
		CHERRY,
		POINT
	}type_object;

	typedef struct {
		void *cell;
		enum type_cell;
		enum type_object;
	}state_cell;



	// functions




#endif /* LOGICAL_TYPE_H_ */
