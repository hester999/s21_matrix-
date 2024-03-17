#include <iostream>
#include <stdio.h>
#include "s21_matrix_oop.h"


// Функция для печати матрицы

int main() {
    S21Matrix matrix1(2, 2);
    matrix1.setValue(0, 0, 5);
    matrix1.setValue(0, 1, 6);
    matrix1.setValue(1, 0, 7);
    matrix1.setValue(1, 1, 8);

    S21Matrix matrix2(2, 2);
    matrix2.setValue(0, 0, 1);
    matrix2.setValue(0, 1, 2);
    matrix2.setValue(1, 0, 3);
    matrix2.setValue(1, 1, 4);

    S21Matrix result = matrix1 - matrix2;
    result.PrintMatrix(result);



    return 0;
}