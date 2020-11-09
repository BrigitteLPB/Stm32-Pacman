/*
 * TFT_advance.c
 *
 *  Created on: 25 oct. 2020
 *      Author: BrigitteLPB
 */
#include "TFT_advanced.h"
// include
#include "TFT_image_alloc.h"


// const



// private prototype



// function
void TFT_avanced_init(TFT_orientation_e orientation){
	TFT_init(orientation);
	IMG_ALLOC_init();
}

TFT_object_s TFT_make_triangle(pos_s xy1, pos_s xy2, pos_s xy3, TFT_color_e color, bool_e filled){
	// init
	TFT_object_s return_value;

	// code
	return_value.color = color;
	return_value.filled = filled;
	return_value.nb_points = 3;
	return_value.points[0] = xy1;
	return_value.points[1] = xy2;
	return_value.points[2] = xy3;

	// end
	return return_value;
}

TFT_object_s TFT_make_rect(pos_s top_left, pos_s bottom_right, TFT_color_e color, bool_e filled){
	// init
	TFT_object_s rect;
		TFT_init_object(&rect);

	// code
	rect.color = color;
	rect.filled = filled;
	rect.nb_points = 4;
	rect.points[0] = top_left;
	rect.points[1] = (pos_s){top_left.y, bottom_right.x};
	rect.points[2] = bottom_right;
	rect.points[3] = (pos_s){bottom_right.y, top_left.x};

	// end
	return rect;
}

TFT_text_s TFT_make_text(char* text, pos_s top_left, TFT_text_size_e font, TFT_color_e foreground, TFT_color_e background){
	TFT_text_s text_construct;
	text_construct.text = text;
	text_construct.backgroud = background;
	text_construct.foreground = foreground;
	text_construct.font = font;
	text_construct.top_left = top_left;

	return text_construct;
}

TFT_image_s TFT_make_image(pos_s top_left, uint16_t height, uint16_t width){
	TFT_image_s image;

	image.height = height;
	image.width = width;
	image.position = top_left;
	image.begin = IMG_ALLOC_new(width, height);

	return image;
}

void TFT_put_text(TFT_text_s* text){
	FontDef_t *font = NULL;
	switch(text->font){
		#if USE_FONT7x10
			case FONT_7x10:
				font = &Font_7x10;
				break;
		#endif
		#if USE_FONT11x18
			case FONT_11x18:
				font = &Font_11x18;
				break;
		#endif
		#if USE_FONT16x26
			case FONT_16x26:
				font = &Font_16x26;
				break;
		#endif
			default:
				font = NULL;
				break;
	}

	ILI9341_Puts((uint16_t) text->top_left.x, (uint16_t) text->top_left.y, text->text, font, (uint16_t) text->foreground, (uint16_t) text->backgroud);
}

void TFT_clean_text(TFT_text_s* text, TFT_color_e background){
	TFT_text_s copy = *text;
	copy.foreground = background;
	copy.backgroud = background;

	TFT_put_text(&copy);
}

void TFT_put_image(TFT_image_s* image){
	ILI9341_putImage(image->position.x,image->position.y, image->width, image->height, image->begin, image->height*image->width);
}


void TFT_test_avanced(void){
	TFT_object_s rect = TFT_make_rect((pos_s){100,150}, (pos_s){200, 250}, COLOR_BLUE, TRUE);

	TFT_object_s triangle = TFT_make_triangle((pos_s){20,250}, (pos_s){60, 270}, (pos_s){60, 230}, COLOR_GREEN, TRUE);

	TFT_draw_object(&rect);
	TFT_draw_object(&triangle);

#if USE_FONT7x10
	TFT_text_s text = TFT_make_text("FONT_7x10", (pos_s){20, 10}, FONT_7x10, COLOR_WHITE, COLOR_BLACK);
	TFT_put_text(&text);
#endif
#if USE_FONT11x18
	TFT_text_s text2 = TFT_make_text("FONT_11x18", (pos_s){40, 10}, FONT_11x18, COLOR_WHITE, COLOR_BLACK);
	TFT_put_text(&text2);
#endif
#if USE_FONT16x26
	TFT_text_s text3 = TFT_make_text("FONT_16x26", (pos_s){60, 10}, FONT_16x26, COLOR_WHITE, COLOR_BLACK);
	TFT_put_text(&text3);
#endif

	TFT_image_s image = TFT_make_image((pos_s){100, 100}, 40, 40);

	if(image.begin != NULL){
		TFT_color_e colors[5] = {COLOR_NONE, COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_BLACK};

		for(uint16_t i=0; i<image.height*image.width; i++){
			*(image.begin + sizeof(TFT_color_e) * i) = colors[i%5];
		}

		TFT_put_image(&image);
	}
}

