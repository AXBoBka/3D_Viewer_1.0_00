#ifndef SRC_S21_3DVIEWER_H_
#define SRC_S21_3DVIEWER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib_matrix/s21_matrix.h"

typedef struct facets {
	int     *vertexes;
	int     numbers_of_vertexes_in_facets;
}           polygon_t;

typedef struct data {
    int         count_of_vertexes;
    int         count_of_facets;
    matrix_t    matrix_3d;
    polygon_t   *polygons;
}               t_data;

int     s21_3D_Viewer(char *str, t_data *data_Obj);
int     objLoader(char* str, t_data *data_Obj);
int     read_File_And_Fill_Data_Obj(t_data *data_Obj, char *str, char *str_obj);
void    counting_The_Number_Of_Vertexes(char *str_obj, int count, t_data *data_Obj);
void    record_Vertexes_To_Poligon_Mas(char *str_obj, int count, t_data *data_Obj);

int err_Open_File(FILE **fp, char *str);
// HELP
void dispaly_Massive_Structure(t_data *data_Obj, char *Name);

#endif  // SRC_S21_3DVIEWER_H_