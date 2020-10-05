/**
 * @file	joystick.c
 * @brief	Definition for abstract module for a module
 * @author	Th�o Guillemaud, Th�o Malinge--Lecompte
 */

// include
#include "joystick.h"
#include "systick.h"
#include "stdbool.h"

static volatile bool FLAG_1S = false;

// const
	typedef adc_id_e ADC_CHANNEL;
	#define MILIEU (uint8_t)2048
	#define TOLERANCE_MAX 1.05
	#define TOLERANCE_MIN 0.95
	#define abs(x) ((x<0)?-x:x)


//prototype
	static JOYSTICK_direction PRIVATE_JOYSTICK_getDirection(ADC_CHANNEL X, ADC_CHANNEL Y);

	static void process_ms();



// private function
	JOYSTICK_direction PRIVATE_JOYSTICK_getDirection(ADC_CHANNEL X, ADC_CHANNEL Y){
		 int16_t X_value = ADC_getValue(X);
		 int16_t Y_value = ADC_getValue(Y);
		if (X_value>MILIEU*TOLERANCE_MIN && X_value<TOLERANCE_MAX && Y_value>MILIEU*TOLERANCE_MIN && Y_value<TOLERANCE_MAX){
			return MILIEU;
		}
		else if (X_value>MILIEU*TOLERANCE_MAX && abs(Y_value-2048)<(X_value-2048)){
			return DROITE;
		}
		else if(Y_value>MILIEU*TOLERANCE_MAX && abs(X_value-2048)<=(Y_value-2048)){
			return HAUT;
		}
		else if(X_value<MILIEU*TOLERANCE_MIN && abs(Y_value-2048)<abs(X_value-2048)){
			return GAUCHE;
		}
		else{
			return BAS;
		}
	 }

	void process_ms(){
		volatile uint16_t t = 0;

		if(!t){
			t= 1000;
			FLAG_1S = true;
		}else{
			FLAG_1S = false;
		}
		t--;
	}


// function

	void JOYSTICK_init(){
		ADC_init();
	}

	 JOYSTICK_direction JOYSTICK_getDirection(JOYSTICK_id id){
		 if(id==JOYSTICK1){
			 return PRIVATE_JOYSTICK_getDirection(X1, Y1);
		 }
		 else{
			 return PRIVATE_JOYSTICK_getDirection(X2 , Y2);
		 }
	 }

	 void JOYSTICK_test(){
		 Systick_add_callback_function(&process_ms);

		 while(true){
			 if(FLAG_1S){
				 JOYSTICK_direction dir = JOYSTICK_getDirection(JOYSTICK1);

				 switch(dir){
				 	 case NEUTRE:
				 		 printf("NEUTRE");
				 		 break;
				 	 case HAUT:
				 		 printf("HAUT");
				 		 break;
				 	 case BAS:
				 		 printf("BAS");
				 		 break;
				 	 case DROITE:
				 		 printf("DROITE");
				 		 break;
				 	 case GAUCHE:
				 		 printf("GAUCHE");
				 		 break;
				 }
				 printf("\n");
			 }
		 }
	 }

