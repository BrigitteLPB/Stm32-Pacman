/**
 * @file	TFT_basic.c
 * @brief	définition des fonctions de dessin généraliser
 * @author	Théo GUILLEMAUD
 */
#include "TFT_basic.h"

// const
typedef struct {
	double	m;
	uint16_t p;
	bool_e no_x;	// true si l'equation est du type x=c
}droite_s;

// prototype de fonction privé
/**
 * @brief			dessine un triangle rempli
 * @param	point_1	premier point
 * @param	point_2	second point
 * @param	point_3	troisième point
 */
static void PRIVATE_TFT_draw_filled_triangle(const pos_s *point_1, const pos_s *point_2, const pos_s *point_3, TFT_color_e color);

/**
 * @brief			dessine l'objet avec des lignes
 * @param object	l'objet à dessiner
 */
static void PRIVATE_TFT_draw_object_line(const TFT_object_s *object);

/**
 * @brief			dessine l'objet avec des lignes
 * @param object	l'objet à dessiner
 */
static void PRIVATE_TFT_draw_object_fill(const TFT_object_s *object);

/**
 * @brief	creer une equation de droite
 * @param	A	le point A
 * @param	B	le point B
 */
static droite_s PRIVATE_TFT_find_straigth_line(pos_s *A, pos_s *B);

/**
 * @brief	trouve le point milieu entre les 3 points selon le x
 */
static pos_s* PRIVATE_TFT_find_middle(pos_s *A, pos_s *B, pos_s *C);

/***
 * @brief	trouve la droite où ne passe pas le sommet
 */
static droite_s* PRIVATE_TFT_find_base(droite_s *d1, droite_s *d2, droite_s *d3, pos_s *sommet);


// fonction
void TFT_init(TFT_orientation_e orientation){
	ILI9341_Init();
	ILI9341_Rotate((ILI9341_Orientation_t) orientation);
}

void TFT_clear(TFT_color_e background_color){
	ILI9341_Fill((uint16_t) background_color);
}

void TFT_draw_object(const TFT_object_s *object){
	//init

	//code
	if( object->nb_points == 0){
		return;
	}else{
		if( object->filled ){
			PRIVATE_TFT_draw_object_fill(object);
		}else{
			PRIVATE_TFT_draw_object_line(object);
		}
	}
}

void TFT_clean_object(const TFT_object_s *object, TFT_color_e background_color){
	//init
	TFT_object_s temp_object = *object;
	temp_object.filled = TRUE;
	temp_object.color = background_color;

	//code
	TFT_draw_object(&temp_object);
}

void TFT_test_basic(void){
	//init
	TFT_object_s object_1;
		object_1.color = COLOR_BLACK;
		object_1.filled = TRUE;
		object_1.points[0].x = 10;
		object_1.points[0].y = 10;
		object_1.points[1].x = 120;
		object_1.points[1].y = 20;
		object_1.points[2].x = 240;
		object_1.points[2].y = 140;
		object_1.points[3].x = 80;
		object_1.points[3].y = 200;
		object_1.points[4].x = 20;
		object_1.points[4].y = 120;
		object_1.nb_points = 5;

	TFT_object_s object_2;
		object_2.color = COLOR_BLUE;
		object_2.filled = FALSE;
		object_2.points[0].x = 180;
		object_2.points[0].y = 30;
		object_2.points[1].x = 300;
		object_2.points[1].y = 10;
		object_2.points[2].x = 200;
		object_2.points[2].y = 200;
		object_2.points[3].x = 150;
		object_2.points[3].y = 220;
		object_2.points[4].x = 50;
		object_2.points[4].y = 170;
		object_2.nb_points = 5;

	TFT_object_s line_1;
		line_1.color = COLOR_BLACK;
		line_1.filled= FALSE;
		line_1.nb_points = 2;
		line_1.points[0] = (pos_s){0, 0};
		line_1.points[1].y = ILI9341_WIDTH;
		line_1.points[1].x = ILI9341_HEIGHT;

	TFT_object_s line_2;
		line_2.color = COLOR_BLACK;
		line_2.filled= FALSE;
		line_2.nb_points = 2;
		line_2.points[0].y = 0;
		line_2.points[0].x = ILI9341_HEIGHT;
		line_2.points[1].y = ILI9341_WIDTH;
		line_2.points[1].x = 0;

	//code
	TFT_draw_object(&object_1);
	TFT_draw_object(&object_2);
	TFT_draw_object(&line_1);
	TFT_draw_object(&line_2);

}

void PRIVATE_TFT_draw_filled_triangle(const pos_s *A, const pos_s *B, const pos_s *C, TFT_color_e color){
	// les triangles ne seront pas remplis car la technique est trop dure

	// init
	const pos_s *points[] = {A, B, C};

	droite_s dAB = PRIVATE_TFT_find_straigth_line(A, B);
	droite_s dBC = PRIVATE_TFT_find_straigth_line(B, C);
	droite_s dCA = PRIVATE_TFT_find_straigth_line(C, A);

	pos_s *point_milieu = PRIVATE_TFT_find_middle(A, B, C);
	droite_s *base =

	//code


}

droite_s PRIVATE_TFT_find_straigth_line(pos_s *A, pos_s *B){
	// init
	droite_s droite;

	// code
	if(A->x == B->x){
		droite.no_x = TRUE;
		droite.m = 0;
		droite.p = 0;
	}else{
		droite.m = (B->y - A->y)/(B->x - A->x);		// m = (yB-yA)/(xB-xA)
		droite.p = A->y - (droite.m * A->x);		// p = yA - m*xA
	}

	// end
	return droite;
}

position PRIVATE_TFT_compute_straigth

pos_s* PRIVATE_TFT_find_middle(pos_s *A, pos_s *B, pos_s *C){
	// init
	position min = MIN(MIN(A->x, B->x), C->x);
	position max = MAX(MAX(A->x, B->x), C->x);

	pos_s *points[] = {A, B, C};

	// code
	for(int i=0; i<3; i++){
		if(points[i]->x != min && points[i]->x != max){
			return points[i];
		}
	}
}

droite_s* PRIVATE_TFT_find_base(droite_s *d1, droite_s *d2, droite_s *d3, pos_s *sommet){

}

void PRIVATE_TFT_draw_object_line(const TFT_object_s *object){
	// init

	//code
	if( object->nb_points < 2 ){
		ILI9341_DrawPixel((uint16_t) object->points[0].x, (uint16_t) object->points[0].y, object->color);
	}else{
		for(int i = 0; i < object->nb_points; i++){
//			ASSERT_T(i == object->nb_points, "L'indice a dépassé la taille du tableau de points d'objet");
			ILI9341_DrawLine(
					(uint16_t) object->points[i].x,
					(uint16_t) object->points[i].y,
					(uint16_t) object->points[(i+1)%object->nb_points].x,
					(uint16_t) object->points[(i+1)%object->nb_points].y,
					object->color
			);
		}
	}
}

void PRIVATE_TFT_draw_object_fill(const TFT_object_s *object){
	// init

	//code
	if( object->nb_points < 3 ){
		PRIVATE_TFT_draw_object_line(object);
	}else{
		for(int i = 1; i < object->nb_points - 1; i++){
//			ASSERT_T(i == object->nb_points, "L'indice a dépassé la taille du tableau de points d'objet");
			PRIVATE_TFT_draw_filled_triangle(
					&object->points[0],
					&object->points[i],
					&object->points[i+1],
					object->color
			);
		}
	}
}

