/*
 * rand.c
 *
 *  Created on: 14 oct. 2020
 *      Author: guill
 */
#include "rand.h"
// include
#include "systick.h"


// const
static volatile uint8_t	values[MAX_VALUES_COUNT];
static volatile uint8_t	index;
static volatile uint8_t	n;

static volatile bool_e init = FALSE;

static volatile bool_e RAND_capture = FALSE;

#define TIME_TO_CATCH	10	// temp en ms avant la capture


// private prototype
static void PRIVATE_RAND_process_ms();



// function
void PRIVATE_RAND_process_ms(){
	static uint8_t time = 0;

	if(time == TIME_TO_CATCH){
		RAND_capture = TRUE;
		time = 0;
	}

	time++;
	n++;
}

void RAND_init(){
	if(!init){
		Systick_add_callback_function(&PRIVATE_RAND_process_ms);
		n=0;
		index=0;

		init = TRUE;

		// filled up the values
		while(index < MAX_VALUES_COUNT){
			RAND_catch_event();
		}
	}
}

void RAND_catch_event(){
	if(RAND_capture){
		uint16_t v = (uint16_t)ADC_getValue(ADC_RAND_PORT);
		uint16_t r = 0;

		if(v == 0){
			r = (uint16_t)ADC_getValue(ADC_REDUNDANCY_PORT);
		}

		uint8_t compute_value = (uint8_t) (n << 2 | (v + r));

		if(index < MAX_VALUES_COUNT){
			values[index] = compute_value;
			index++;
		}

		RAND_capture = FALSE;
	}
}

uint8_t RAND_get(void){
	uint8_t return_value;

	if(index == 0){
		return 0;
	}else{
		return_value = values[0];

		// move values
		for(uint8_t i = 0; i < index-1; i++){
			values[i] = values[i+1];
		}
		index--;

		return return_value;
	}

}
