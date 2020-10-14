/*
 * rand.h
 *
 *  Created on: 14 oct. 2020
 *      Author: guill
 */

#ifndef ABSTRACT_RAND_RAND_H_
#define ABSTRACT_RAND_RAND_H_

	// include
	#include "stm32f1_adc.h"


	// const
	#define MAX_VALUES_COUNT	16		// max numbers catch

	#define	ADC_RAND_PORT ADC_0			// the port used to generate rand
	#define	ADC_REDUNDANCY_PORT ADC_1	// redundacy port used


	// function
	/**
	 * @pre	initialize ADC
	 */
	void RAND_init(void);

	/**
	 * 	call regularly this function to get new values
	 */
	void RAND_catch_event(void);

	uint8_t RAND_get(void);



#endif /* ABSTRACT_RAND_RAND_H_ */
