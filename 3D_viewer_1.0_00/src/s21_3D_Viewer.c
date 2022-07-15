#include "s21_3D_Viewer.h"

void dispaly_Massive_Structure(t_data *data_Obj, char *Name) {  // sega x3
    int i = 0;
    int count = 1;

    // printf("%p\n", data_Obj->polygons[1]);
    printf("%s\n", Name);
    // while (count <= data_Obj->count_of_vertexes) {
    //     i = 0;
    //     while (data_Obj->polygons[count].vertexes[i]) {
    //         printf("%d ", data_Obj->polygons[count].vertexes[i]);
    //         i++;
    //     }
    //     printf("\n");
    //     count++;
    // }

}

int err_Open_File(FILE **fp, char *str) {
    int ret = 0;

    *fp = fopen(str,"r");
    printf("STR = %s\n", str);
    if(*fp == NULL) {
        printf("Error");
        ret = 1;
    }

    return (ret);
}

void record_Vertexes_To_Poligon_Mas(char *str_obj, int count, t_data *data_Obj) {
    int i = 0;
    int fl = 1;
    int num_vertexes = 0;

    data_Obj->polygons[count].vertexes = (int *)calloc(data_Obj->polygons[count].numbers_of_vertexes_in_facets, sizeof(int));

    while (str_obj[i]) {
        if (strchr("0123456789", str_obj[i]) && fl) {
            data_Obj->polygons[count].vertexes[num_vertexes] = atof(str_obj + i);
            while (strchr("0123456789.", str_obj[i])) {
                i++;
            }
            fl = 0;
            num_vertexes++;
        }
        if (str_obj[i] == ' ') {
            fl = 1;
        }
        i++;
    }

}

void counting_The_Number_Of_Vertexes(char *str_obj, int count, t_data *data_Obj) {
    int i = 0;
    int fl = 1;
    
    while (str_obj[i]) {
        if (strchr("0123456789", str_obj[i]) && fl) {
            while (strchr("0123456789.", str_obj[i])) {
                i++;
            }
            data_Obj->polygons[count].numbers_of_vertexes_in_facets++;
            fl = 0;
        }
        if (str_obj[i] == ' ') {
            fl = 1;
        }

        // if (str_obj[i] == '/') {
        //     if (str_obj[i] + 1 != '/') {
        //         while (strchr("0123456789.", str_obj[i])) {
        //             i++;
        //         }
        //     }
        //     if (type == 1)
        //         type = 2;
        //     else if (type == 2)
        //         type = 3;
        // }
        i++;
    }
    // printf("%d\n", data_Obj->polygons[count].numbers_of_vertexes_in_facets);
}

int read_File_And_Fill_Data_Obj(t_data *data_Obj, char *str, char *str_obj) {
    int ret = 0;
    FILE *fp = NULL;

    ret = err_Open_File(&fp, str);

    if (!ret) {
        int i = 1;
        int count = 1;
         while (fgets(str_obj, 1024, fp)) {
            if (strstr(str_obj, "v ") && str_obj[1] == ' ') {
                // printf("%s", str_obj);
                double x = 0.0;
                double y = 0.0;
                double z = 0.0;
                sscanf(str_obj + 3, "%lf%lf%lf", &x, &y, &z);
                data_Obj->matrix_3d.matrix[i][0] = x;
                data_Obj->matrix_3d.matrix[i][1] = y;
                data_Obj->matrix_3d.matrix[i][2] = z;
                i++;
            }

            if (strstr(str_obj, "f ") && str_obj[1] == ' ') {
                counting_The_Number_Of_Vertexes(str_obj, count, data_Obj);
                record_Vertexes_To_Poligon_Mas(str_obj, count, data_Obj);
                count++;
            }
            // if (strstr(str_obj, "f ") && str_obj[1] == ' ') {
            //     data_Obj->count_of_facets++;
            // }
        }
    }
    display_matrix(data_Obj->matrix_3d, 2, "data_Obj");
    dispaly_Massive_Structure(data_Obj, "Polygons_mas");
    return (ret);
}

int objLoader(char* str, t_data *data_Obj) {
    int ret = 0;
    FILE *fp = NULL;
    char str_obj[1024] = {0}; 

    ret = err_Open_File(&fp, str);
    // fp = fopen(str,"r");
    // if(fp == NULL) {
    //     printf("Error!");   
    //     ret = 1;
    // }

    if (!ret) {
        while (fgets(str_obj, 1024, fp)) {
            // printf("%s", str_obj);
            if (strstr(str_obj, "v ") && str_obj[1] == ' ') {
                data_Obj->count_of_vertexes++;
            }

            if (strstr(str_obj, "f ") && str_obj[1] == ' ') {
                data_Obj->count_of_facets++;
            }
        }
        // printf("\n%d %d\n", data_Obj->count_of_vertexes, data_Obj->count_of_facets);
    }
    if (!ret) {
        ret = s21_create_matrix(data_Obj->count_of_vertexes + 1, 3, &(data_Obj->matrix_3d));
        data_Obj->polygons = (polygon_t *)calloc(data_Obj->count_of_facets + 1, sizeof(polygon_t));
        if (!data_Obj->polygons) ret = 1;
        if (!ret) {
            ret = read_File_And_Fill_Data_Obj(data_Obj, str, str_obj);
        }
    }

    return (ret);
}

int s21_3D_Viewer(char *str, t_data *data_Obj) {
    int ret = 0;

    // char str_file[100] = "3D_models(OBJ)/easyCube.obj";
    ret = objLoader(str, data_Obj);

    return (ret);
}