/**
 * @file	joystick.c
 * @brief	Definition for abstract module for a module
 * @author	Théo Guillemaud
 */
#include "joystick.h"
// include
#include "stm32f1_adc.h"

// const
#define X ADC_0
#define Y ADC_1

// private function



// function
void JOYSTICK_init(){
	ADC_init();
}

void JOYSTICK_test(){
	printf("X: %d\n", ADC_getValue(X));
	printf("Y: %d\n", ADC_getValue(Y));
	abs(34);
	abs(34);
}
