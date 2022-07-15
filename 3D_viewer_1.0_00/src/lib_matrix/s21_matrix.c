#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int ret = 0;

    result->rows = rows;
    result->columns = columns;

    if (rows < 1 || columns < 1) {
        ret = 1;
    } else if (rows > 0 && columns > 0) {
        result->matrix = (double **)calloc(rows, sizeof(double *));

        for (int i = 0; i < rows; i++) {
            result->matrix[i] = (double *)calloc(columns, sizeof(double));
        }
    }

    return (ret);
}

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
    }

    if (A->rows) {
        A->rows = 0;
    }

    if (A->columns) {
        A->columns = 0;
    }

    if (A->matrix) {
        free(A->matrix);
        A->matrix = NULL;
    }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int ret = FAILURE;
    int stop = 0;

    ret = incorrect_matrix(A);
    if (!ret) ret = incorrect_matrix(B);

    if (!ret) {
        ret = SUCCESS;
        if (A->columns == B->columns && A->rows == B->rows) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
                        ret = FAILURE;
                        stop = 1;
                        break;
                    }
                }

                if (stop) {
                    break;
                }
            }
        } else {
            ret = FAILURE;
        }
    } else if (ret) {
        ret = FAILURE;
    }

    return (ret);
}

int add_or_sub(matrix_t *A, matrix_t *B, matrix_t *result, int add_or_sub) {  // add = 1; sub = -1;
    int ret = 0;

    ret = incorrect_matrix(A);
    if (!ret) incorrect_matrix(B);
    if (A->columns == B->columns && A->rows == B->rows && !ret) {
        ret = s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] + (add_or_sub * B->matrix[i][j]);
            }
        }
    } else if (!ret) {
        ret = 2;
    }

    return (ret);
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int ret = 1;

    ret = add_or_sub(A, B, result, 1);

    return (ret);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int ret = 1;

    ret = add_or_sub(A, B, result, -1);

    return (ret);
}

int incorrect_matrix(matrix_t *M) {
    int ret = 0;

    if (M == NULL || M->matrix == NULL || M->rows <= 0 || M->columns <= 0) {
        ret = 1;
    }

    return (ret);
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int ret = 0;

    if (!ret) ret = incorrect_matrix(A);

    if (!ret) {
        ret = s21_create_matrix(A->rows, A->columns, result);
        if (!ret) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] * number;
                }
            }
        }
    }

    return (ret);
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int ret = 0;

    ret = incorrect_matrix(A);
    if (!ret) ret = incorrect_matrix(B);

    if (A->columns == B->rows && !ret) {
        ret = s21_create_matrix(A->rows, B->columns, result);
        if (!ret) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < B->columns; j++) {
                    for (int k = 0; k < B->rows; k++) {
                        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                    }
                }
            }
        }
    } else if (!ret) {
        ret = 2;
    }

    return (ret);
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int ret = 0;

    if (!ret) ret = incorrect_matrix(A);

    if (A->rows && A->columns && !ret) {
        ret = s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
    } else if (!ret) {
        ret = 2;
    }

    return (ret);
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int ret = 0;

    ret = incorrect_matrix(A);
    if (A->columns == A->rows && !ret) {
        ret = s21_create_matrix(A->rows, A->columns, result);
        if (!ret) {
            result->matrix[0][0] = 1;
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->rows; j++) {
                    double res = 0.0;
                    matrix_t minor = {0};
                    ret = Minor(i + 1, j + 1, A, &minor);
                    if (!ret)
                        ret = s21_determinant(&minor, &res);
                    if (!ret)
                        result->matrix[i][j] = pow((-1), i + j) * res;
                    s21_remove_matrix(&minor);
                }
            }
        }
    } else if (!ret) {
        ret = 2;
    }

    return (ret);
}

int Minor(int row, int column, matrix_t *A, matrix_t *result) {
    int ret = 1;

    if (A->matrix != NULL) {
        ret = s21_create_matrix(A->rows - 1, A->columns - 1, result);
        if (!ret) {
            int k = 0;
            int z = 0;
            for (int i = 0; i < A->rows; i++) {
                k = i;
                if (k > row - 1) {
                    k--;
                }

                for (int j = 0; j < A->columns; j++) {
                    z = j;
                    if (z > column - 1) {
                        z--;
                    }

                    if (i != (row - 1) && j != (column - 1))
                        result->matrix[k][z] = A->matrix[i][j];
                }
            }
        }
    }

    return (ret);
}

double s21_help_determinant(matrix_t *A) {
    int ret = 0;
    double res = 0.0;

    if (A->rows == 2 && A->columns == 2) {
        res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
        for (int i = 0; i < A->rows; i++) {
            matrix_t M;
            ret = Minor(1, i + 1, A, &M);
            display_matrix(M, 2, "Minor");
            if (!ret)
                res += pow((-1), i) * A->matrix[0][i] * s21_help_determinant(&M);
            s21_remove_matrix(&M);
        }
    }

    return (res);
}

int s21_determinant(matrix_t *A, double *result) {
    int ret = 0;

    if (!ret)
        ret = incorrect_matrix(A);

    if (A->rows == A->columns && !ret) {
        *result = A->matrix[0][0];
        if (A->rows > 1) {
            *result = s21_help_determinant(A);
        }
    } else {
        ret = 1;
    }

    return (ret);
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int ret = 0;

    ret = incorrect_matrix(A);

    if (!ret) {
        double det = 0.0;
        double eps = pow(10, -7);

        ret = s21_determinant(A, &det);

        if ((fabs(det - 0) >= eps) && !ret) {
            matrix_t tmp_calc = {0};
            ret = s21_calc_complements(A, &tmp_calc);
            if (!ret) {
                matrix_t tmp_transpose = {0};
                ret = s21_transpose(&tmp_calc, &tmp_transpose);
                if (!ret) {
                    s21_mult_number(&tmp_transpose, (1.0 / det), result);
                }
                s21_remove_matrix(&tmp_transpose);
            }
            s21_remove_matrix(&tmp_calc);
        }
    }

    return (ret);
}

void display_matrix(matrix_t mat, int line_break, char *Name) {
    if (line_break == 3) {
        printf("\n");
        line_break -= 1;
    }

    if (line_break == 1 || line_break == 2) {
        printf("\n");
    }

    int i = 0;
    printf("%s\n", Name);

    while (i < mat.rows) {
        int j = 0;
        while (j < mat.columns) {
            printf("%-15.3lf ", mat.matrix[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }

    if (line_break == 2) {
        printf("\n");
    }
}

int filling_matrix(matrix_t *M, int min, int max) {
    int ret = 0;

    srand(time(NULL));
    int sign  = 1;
    for (int i = 0; i < M->rows; i++) {
        for (int j = 0; j < M->columns; j++) {
            M->matrix[i][j] = sign * (double)rand() / (max * (min - 0.01) + 0.01);
            sign *= -1;
        }
    }

    return (ret);
}
