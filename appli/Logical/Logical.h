/*
 * Logical.h
 *
 *  Created on: 22 sept. 2020
 *      Author: guill
 */

#ifndef LOGICAL_LOGICAL_H_
#define LOGICAL_LOGICAL_H_

	// single include for the game logic
#include "Abstract/Joystick/joystick.h"
#include "type.h"
#include "stm32f1_ili9341.h"




void mouvement(JOYSTICK_direction direction);
void initWALL();
void fantome_mvt();


#endif /* LOGICAL_LOGICAL_H_ */