/*
 * display.h
 *
 *  Created on: 2 nov. 2020
 *      Author: guill
 */

#ifndef DISPLAY_RENDERER_RENDERER_H_
	#define DISPLAY_RENDERER_RENDERER_H_

	// include


	// const
	typedef enum {
		GHOST_1,
		GHOST_2,
		GHOST_3,
		GHOST_4
	}RENDERER_ghost_e;


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
	 * @brief	test l'affichage
	 */
	void RENDERER_test();

#endif /* DISPLAY_RENDERER_RENDERER_H_ */
