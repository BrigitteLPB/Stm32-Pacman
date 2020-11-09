/*
 * TFT_image_alloc.h
 *
 *  Created on: 4 nov. 2020
 *      Author: guill
 */

#ifndef ABSTRACT_TFT_TFT_IMAGE_ALLOC_H_
#define ABSTRACT_TFT_TFT_IMAGE_ALLOC_H_

	// include
	#include "macro_types.h"
	#include "TFT_basic.h"


	// const
	#define	MAX_IMG_COUNT	10		// maxium number of images loaded
	#define	BUFFER_SIZE		2048	// numbers of octets dedicated to image

	typedef TFT_color_e data_t;

	// function
	void IMG_ALLOC_init(void);

	data_t* IMG_ALLOC_new(uint16_t x_size, uint16_t y_size);

	void IMG_ALLOC_delete(data_t* address);


#endif /* ABSTRACT_TFT_TFT_IMAGE_ALLOC_H_ */
