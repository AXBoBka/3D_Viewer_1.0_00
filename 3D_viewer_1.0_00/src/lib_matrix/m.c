#include "s21_matrix.h"

int main() {
    int ret = 0;
    double ratio = 0;
    double det = 1;
    int i = 0, j = 0, k = 0, n = 0;
    double res = 0.0;

    matrix_t M1 = {0};
    matrix_t M2;
    matrix_t result = {0};

    scanf("%d", &n);
    s21_create_matrix(n, n, &M1);
    // s21_create_matrix(3, 3, &M2);
    // s21_create_matrix(3, 3, &result);

    filling_matrix(&M1, 100000, 1010);
    // filling_matrix(&M2, 101000, 1010);
    // filling_matrix(&result, 10100, 20000);


    ret = s21_determinant(&M1, &res);
    // ret = s21_sub_matrix(&M2, &M1, &result);
    // ret = s21_transpose(&M1, &result);
    // ret = s21_mult_matrix(&M1, &M2, &result);
    // ret = s21_calc_complements(&M1, &result);
    // ret = s21_inverse_matrix(&M1, &result);
    // ret = Minor(1, 1, &M2, &result);
    // ret = s21_eq_matrix(&result, &M2);

    display_matrix(M1, 2, "M1");
    // display_matrix(M2, 0, "M2");
    display_matrix(result, 3, "result");
    printf("Determenant = %lf\n", res);
    printf("\nreturn = %d\n", ret);

    return (0);
    }
