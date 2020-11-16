/*
 * display.h
 *
 *  Created on: 2 nov. 2020
 *      Author: guill
 */

#ifndef DISPLAY_RENDERER_RENDERER_H_
	#define DISPLAY_RENDERER_RENDERER_H_

	// include
	#include "../../Logical/type.h"

	// const



	// function
	/**
	 * @brief	initialise l'affichage
	 */
	void RENDERER_init(void);

	/**
	 * @brief	de-initialise l'affichage
	 */
	void RENDERER_kill(void);

	/**
	 * @brief	kill and init
	 */
	void RENDERER_reset(void);

	/**
	 * @brief	show the game in the map
	 */
	void RENDERER_show(game_s *game);

	/**
	 * @brief	test l'affichage
	 */
	void RENDERER_test();

#endif /* DISPLAY_RENDERER_RENDERER_H_ */
