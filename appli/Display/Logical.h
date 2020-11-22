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
#include "stdbool.h"
#include <stdlib.h>

void initMAP();
void refreshMAP();
state_game jeu();




#endif /* LOGICAL_LOGICAL_H_ */
