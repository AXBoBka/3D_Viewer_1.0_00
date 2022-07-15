#include "s21_3D_Viewer.h"

int main () {
    int ret = 0;
    t_data data_Obj = {0};
    char str[100] = "3D_models(OBJ)/cube.obj";
    ret = objLoader(str, &data_Obj);
    return (ret);
}