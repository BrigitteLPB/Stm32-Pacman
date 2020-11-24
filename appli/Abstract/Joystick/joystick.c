/**
 * @file	joystick.c
 * @brief	Definition for abstract module for a module
 * @author	Th�o Guillemaud, Th�o Malinge--Lecompte
 */

// include
#include "joystick.h"


static volatile bool FLAG_1S = false;

// const
	typedef adc_id_e ADC_CHANNEL;
	#define MILIEU (uint16_t) 1850
	#define TOLERANCE_MAX 500
	#define TOLERANCE_MIN -500
	#define abs(x) ((x<0)?-x:x)

//prototype
	static JOYSTICK_direction PRIVATE_JOYSTICK_getDirection(ADC_CHANNEL X, ADC_CHANNEL Y);

// private function
	JOYSTICK_direction PRIVATE_JOYSTICK_getDirection(ADC_CHANNEL X, ADC_CHANNEL Y){
		static int16_t X_value;
		static int16_t Y_value;

		if(ADC_is_new_sample_available()){
			X_value = (int16_t)(ADC_getValue(X)-MILIEU);
			Y_value = (int16_t)(ADC_getValue(Y)-MILIEU);
		}

		printf("X value : %d\n",X_value);
		printf("Y value : %d\n",Y_value);

		if (Y_value<TOLERANCE_MIN && abs(Y_value)>abs(X_value)){
			return BAS;
		}
		else if (X_value>TOLERANCE_MAX && abs(Y_value)<abs(X_value)){
			return GAUCHE;
		}
		else if(Y_value>TOLERANCE_MAX && abs(X_value)<=abs(Y_value)){
			return HAUT;
		}
		else if(X_value<TOLERANCE_MIN && abs(Y_value)<abs(X_value)){
			return DROITE;
		}
		else{
			return NEUTRE;
		}
	 }

	void JOYSTICK_private_process_ms(){
		static uint16_t t = 0;

		if(!t){
			t= 3000;
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
		 Systick_add_callback_function(&JOYSTICK_private_process_ms);

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

