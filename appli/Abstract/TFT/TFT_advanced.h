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

	typedef struct {
		uint16_t	width;
		uint16_t	height;
		pos_s		position;
		TFT_color_e *begin;		// start of the data
	}TFT_image_s;


	// function
	/**
	 * @breif	initialise basic and image
	 */
	void TFT_avanced_init(TFT_orientation_e orientation);

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
	 * @brief	return a struct initialse for an image. begin is NULL if alloc failed
	 */
	TFT_image_s TFT_make_image(pos_s top_left, uint16_t height, uint16_t width);

	/**
	 * @brief	put text
	 */
	void TFT_put_text(TFT_text_s* text);

	/**
	 * @brief	clear the text by adding background colored rect on the text
	 */
	void TFT_clean_text(TFT_text_s* text, TFT_color_e background);

	/**
	 * @brief	put an image on the screen
	 */
	void TFT_put_image(TFT_image_s* image);

	/**
	 * @brief	put an image and change the swapped color by the new
	 */
	void TFT_put_image_swap_color(TFT_image_s* image, TFT_color_e swapped, TFT_color_e new);

	void TFT_fill_image(TFT_image_s* image, TFT_color_e data[]);

	void TFT_test_avanced(void);

#endif /* ABSTRACT_TFT_TFT_ADVANCED_H_ */
