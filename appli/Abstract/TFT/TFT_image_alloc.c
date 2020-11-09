/*
 * TFT_image_alloc.c
 *
 *  Created on: 4 nov. 2020
 *      Author: guill
 */
#include "TFT_image_alloc.h"
// include


// const
typedef struct {
	uint8_t	nb;						// number of imgs
	data_t* index[MAX_IMG_COUNT+1];	// last index is for free
}PRIVATE_indexs_s;

typedef struct {
	uint32_t	size_max;
	uint32_t	free_space;
	data_t		data[BUFFER_SIZE];
}PRIVATE_gallery_s;


// global
static PRIVATE_gallery_s gallery;
static PRIVATE_indexs_s paint_position;

static data_t* last_indicator;


// private prototype


// function
void IMG_ALLOC_init(void){
	paint_position.nb = 0;
	paint_position.index[0] = &gallery.data[0];

	gallery.free_space = BUFFER_SIZE;
	gallery.size_max = BUFFER_SIZE;

	last_indicator = &gallery.data[BUFFER_SIZE-1];
}

data_t* IMG_ALLOC_new(uint16_t x_size, uint16_t y_size){
	if(paint_position.nb == MAX_IMG_COUNT){
		return NULL;
	}else{
		uint32_t size = (uint32_t) (x_size * y_size);
		if(size <= gallery.free_space){
			gallery.free_space -= size;
			paint_position.nb++;
			paint_position.index[paint_position.nb] = paint_position.index[paint_position.nb-1] + size;
			assert(paint_position.index[paint_position.nb-1] == last_indicator && "Renvoie de la derniere adresse");
			return paint_position.index[paint_position.nb-1];
		}else{
			return NULL;
		}
	}
}

void IMG_ALLOC_delete(data_t* address){
	for(int i = 0; i < paint_position.nb; i++){
		if(paint_position.index[i] == address){
			// fragmentation
			uint32_t size_remove = (uint32_t) (paint_position.index[i+1] - paint_position.index[i]);
			for(int j=0; j<= paint_position.index[paint_position.nb] - paint_position.index[i]; j++){
				gallery.data[(uint32_t) (paint_position.index[i] + j - paint_position.index[0])] = gallery.data[(uint32_t) (paint_position.index[i+1] + j - paint_position.index[0])];
			}
			gallery.free_space += size_remove;
			// move array
			for(int idx = i; idx < paint_position.nb; idx++){
				paint_position.index[idx] = paint_position.index[idx+1];
			}
			paint_position.nb--;
			return;
		}
	}
	return;
}
