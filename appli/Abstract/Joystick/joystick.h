/**
 * @file	joystick.h
 * @brief	All declaration to abstract a Joystick
 * @author	Thï¿½o Guillemaud, Thï¿½o Malinge--Lecompte
 */
#ifndef JOYSTICK_H_
	#define JOYSTICK_H_

	// include
	#include "stm32f1_adc.h"

	// const
	#define X1 ADC_1	//joystick nè1
	#define Y1 ADC_0
	#define X2 ADC_9	//joystick n2
	#define Y2 ADC_8

	typedef enum {
		HAUT,
		BAS,
		DROITE,
		GAUCHE,
		NEUTRE
	} JOYSTICK_direction;


	typedef enum {
		JOYSTICK1,
		JOYSTICK2
	}JOYSTICK_id;





	// functions
	void JOYSTICK_init();

	/**
	 * return the direction of the specifid joystick
	 */
	JOYSTICK_direction JOYSTICK_getDirection(JOYSTICK_id id);

	void JOYSTICK_test();

#endif
