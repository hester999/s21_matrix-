#include <gtest/gtest.h>
#include "../s21_matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
    S21Matrix matrix;
    EXPECT_EQ(matrix.getRows(), 0);
    EXPECT_EQ(matrix.getCols(), 0);
}

TEST(S21MatrixTest, ParameterizedConstructor) {
    S21Matrix matrix(3, 3);
    EXPECT_EQ(matrix.getRows(), 3);
    EXPECT_EQ(matrix.getCols(), 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(matrix.getValue(i, j), 0);
        }
    }
}

TEST(S21MatrixTest, CopyConstructor) {
    S21Matrix original(2, 2);
    original.setValue(0, 0, 1.0);
    original.setValue(1, 1, 2.0);
    S21Matrix copy = original;
    EXPECT_EQ(copy.getValue(0, 0), 1.0);
    EXPECT_EQ(copy.getValue(1, 1), 2.0);
}

TEST(S21MatrixTest, SetValueGetValue) {
    S21Matrix matrix(2, 2);
    matrix.setValue(0, 0, 3.14);
    EXPECT_DOUBLE_EQ(matrix.getValue(0, 0), 3.14);
}

TEST(S21MatrixTest, SumMatrix) {
    S21Matrix matrix1(2, 2);
    matrix1.setValue(0, 0, 1);
    matrix1.setValue(0, 1, 2);
    matrix1.setValue(1, 0, 3);
    matrix1.setValue(1, 1, 4);

    S21Matrix matrix2(2, 2);
    matrix2.setValue(0, 0, 5);
    matrix2.setValue(0, 1, 6);
    matrix2.setValue(1, 0, 7);
    matrix2.setValue(1, 1, 8);

    matrix1.SumMatrix(matrix2);

    EXPECT_EQ(matrix1.getValue(0, 0), 6);
    EXPECT_EQ(matrix1.getValue(0, 1), 8);
    EXPECT_EQ(matrix1.getValue(1, 0), 10);
    EXPECT_EQ(matrix1.getValue(1, 1), 12);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
