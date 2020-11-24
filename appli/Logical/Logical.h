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

	void LOGICAL_init(void);

	void LOGICAL_kill(void);

	state_game jeu(uint16_t *score);

#endif /* LOGICAL_LOGICAL_H_ */
