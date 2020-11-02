/*
 * TFT_advanced.h
 *
 *  Created on: 25 oct. 2020
 *      Author: BrigitteLPB
 */

#ifndef ABSTRACT_TFT_TFT_ADVANCED_H_
#define ABSTRACT_TFT_TFT_ADVANCED_H_

	// include
	#include "TFT_basic.h"

	// const
	typedef enum {
		#if USE_FONT7x10
			FONT_7x10
			#if USE_FONT11x18 || USE_FONT16x26
				,
			#endif
		#endif
		#if USE_FONT11x18
			FONT_11x18
			#if USE_FONT16x26
				,
			#endif
		#endif
		#if USE_FONT16x26
			FONT_16x26
		#endif
	}TFT_text_size_e;

	typedef struct {
		char* 			text;
		TFT_color_e 	backgroud;
		TFT_color_e		foreground;
		TFT_text_size_e font;
		pos_s			top_left;
	}TFT_text_s;

	// function
	/**
	 * @return	return a object with a triangle
	 */
	TFT_object_s TFT_make_triangle(pos_s xy1, pos_s xy2, pos_s xy3, TFT_color_e color, bool_e filled);

	/**
	 * @return	return a object to drawn a rect
	 */
	TFT_object_s TFT_make_rect(pos_s top_left, pos_s bottom_right, TFT_color_e color, bool_e filled);

	/**
	 * @brief	return a object to put text
	 */
	TFT_text_s TFT_make_text(char* text, pos_s top_left, TFT_text_size_e font, TFT_color_e foreground, TFT_color_e background);

	/**
	 * @brief	put text
	 */
	void TFT_put_text(TFT_text_s* text);

	/**
	 * @brief	clear the text by adding background colored rect on the text
	 */
	void TFT_clean_text(TFT_text_s* text, TFT_color_e background);

	void TFT_test_avanced(void);

#endif /* ABSTRACT_TFT_TFT_ADVANCED_H_ */
