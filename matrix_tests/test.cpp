#include <gtest/gtest.h>
#include "../s21_matrix_oop.h"
#include <limits.h>

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

TEST(S21MatrixTest, MoveConstructor) {

    S21Matrix temp(3, 3);




    S21Matrix moved(std::move(temp));


    ASSERT_EQ(3, moved.getRows());
    ASSERT_EQ(3, moved.getCols());


    ASSERT_EQ(0, temp.getRows());
    ASSERT_EQ(0, temp.getCols());
    ASSERT_EQ(nullptr, temp.getMatrix());
}

TEST(S21MatrixTest,CreateMatrix_fail){
    S21Matrix matrix;

    EXPECT_THROW(matrix.CreateMatrix(-1,-1), std::length_error);
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

TEST(S21MatrixTest,SetRowCol){

    S21Matrix test(3,3);
    S21Matrix res(4,4);

    test.setCol(4);
    test.setRows(4);
    int ans = (test == res);
    EXPECT_EQ(ans,1);

}

TEST(S21MatrixTest,SetRow_err){

    S21Matrix test(3,3);
    EXPECT_THROW(test.setRows(-1), std::length_error);
}

TEST(S21MatrixTest,SetCol_err){

    S21Matrix test(3,3);
    EXPECT_THROW(test.setCol(-1), std::length_error);
}


TEST(S21MatrixTest, GetValue_err){
    S21Matrix test(3, 3);
    EXPECT_THROW(test.getValue(-1, -1), std::out_of_range);
}

TEST(S21MatrixTest, SetValue_err){
    S21Matrix test(3, 3);
    EXPECT_THROW(test.setValue(-1, -1, 23), std::out_of_range);
}

TEST(S21MatrixTest, Subtraction) {
    S21Matrix matrix1(2, 2);
    S21Matrix matrix2(2, 2);


    matrix1.setValue(0, 0, 1);
    matrix1.setValue(0, 1, 2);
    matrix1.setValue(1, 0, 3);
    matrix1.setValue(1, 1, 4);

    matrix2.setValue(0, 0, 4);
    matrix2.setValue(0, 1, 3);
    matrix2.setValue(1, 0, 2);
    matrix2.setValue(1, 1, 1);


    matrix1.SubMatrix(matrix2);


    ASSERT_EQ(matrix1.getValue(0, 0), -3);
    ASSERT_EQ(matrix1.getValue(0, 1), -1);
    ASSERT_EQ(matrix1.getValue(1, 0), 1);
    ASSERT_EQ(matrix1.getValue(1, 1), 3);
}


TEST(S21MatrixTest, MultiplicationByScalar) {
    // Создаем матрицу
    S21Matrix matrix(2, 2);

    // Заполняем матрицу данными
    matrix.setValue(0, 0, 1);
    matrix.setValue(0, 1, 2);
    matrix.setValue(1, 0, 3);
    matrix.setValue(1, 1, 4);

    // Умножаем матрицу на число
    double scalar = 2.5;
    matrix.MulNumber(scalar);

    // Проверяем результат умножения
    ASSERT_EQ(matrix.getValue(0, 0), 2.5);
    ASSERT_EQ(matrix.getValue(0, 1), 5.0);
    ASSERT_EQ(matrix.getValue(1, 0), 7.5);
    ASSERT_EQ(matrix.getValue(1, 1), 10.0);
}

TEST(S21MatrixTest, Num_isinf){
    S21Matrix test(3, 3);

    EXPECT_THROW(test*=INFINITY, std::length_error);
}


TEST(S21MatrixTest, MatrixMultiplicationByMatrix) {
    // Создаем две матрицы для умножения
    S21Matrix matrix1(2, 2);
    S21Matrix matrix2(2, 2);

    // Заполняем матрицы данными
    matrix1.setValue(0, 0, 1);
    matrix1.setValue(0, 1, 2);
    matrix1.setValue(1, 0, 3);
    matrix1.setValue(1, 1, 4);

    matrix2.setValue(0, 0, 5);
    matrix2.setValue(0, 1, 6);
    matrix2.setValue(1, 0, 7);
    matrix2.setValue(1, 1, 8);

    // Умножаем матрицы
    S21Matrix result = matrix1 * matrix2;

    // Проверяем результат умножения
    ASSERT_EQ(result.getValue(0, 0), 19);
    ASSERT_EQ(result.getValue(0, 1), 22);
    ASSERT_EQ(result.getValue(1, 0), 43);
    ASSERT_EQ(result.getValue(1, 1), 50);
}



TEST(S21MatrixTest, EqMatrix) {
    // Создаем две матрицы для сравнения
    S21Matrix matrix1(2, 2);
    S21Matrix matrix2(2, 2);

    // Заполняем матрицы данными
    matrix1.setValue(0, 0, 1);
    matrix1.setValue(0, 1, 2);
    matrix1.setValue(1, 0, 3);
    matrix1.setValue(1, 1, 4);

    matrix2.setValue(0, 0, 1.0);
    matrix2.setValue(0, 1, 2.0);
    matrix2.setValue(1, 0, 3.0);
    matrix2.setValue(1, 1, 4.0);

    // Проверяем, что матрицы равны с учетом погрешности
    ASSERT_TRUE(matrix1.EqMatrix(matrix2));
}


TEST(S21MatrixTest, Not_EqMatrix) {
    // Создаем две матрицы для сравнения
    S21Matrix matrix1(2, 2);
    S21Matrix matrix2(2, 2);

    // Заполняем матрицы данными
    matrix1.setValue(0, 0, 10);
    matrix1.setValue(0, 1, 20);
    matrix1.setValue(1, 0, 30);
    matrix1.setValue(1, 1, 40);

    matrix2.setValue(0, 0, 1.0);
    matrix2.setValue(0, 1, 2.0);
    matrix2.setValue(1, 0, 3.0);
    matrix2.setValue(1, 1, 4.0);

    // Проверяем, что матрицы равны с учетом погрешности
    ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}


TEST(S21MatrixTest, Transpose) {
    // Создаем матрицу для тестирования
    S21Matrix matrix(2, 3);

    // Заполняем матрицу данными
    matrix.setValue(0, 0, 1);
    matrix.setValue(0, 1, 2);
    matrix.setValue(0, 2, 3);
    matrix.setValue(1, 0, 4);
    matrix.setValue(1, 1, 5);
    matrix.setValue(1, 2, 6);

    // Выполняем транспонирование
    S21Matrix transposed = matrix.Transpose();

    // Проверяем, что размерности матрицы изменились
    EXPECT_EQ(transposed.getRows(), 3);
    EXPECT_EQ(transposed.getCols(), 2);

    // Проверяем значения элементов после транспонирования
    EXPECT_EQ(transposed.getValue(0, 0), 1);
    EXPECT_EQ(transposed.getValue(1, 0), 2);
    EXPECT_EQ(transposed.getValue(2, 0), 3);
    EXPECT_EQ(transposed.getValue(0, 1), 4);
    EXPECT_EQ(transposed.getValue(1, 1), 5);
    EXPECT_EQ(transposed.getValue(2, 1), 6);
}


TEST(S21MatrixTest, Determinant) {

    S21Matrix matrix(3, 3);


    matrix.setValue(0, 0, 1);
    matrix.setValue(0, 1, 2);
    matrix.setValue(0, 2, 3);
    matrix.setValue(1, 0, 4);
    matrix.setValue(1, 1, 5);
    matrix.setValue(1, 2, 6);
    matrix.setValue(2, 0, 7);
    matrix.setValue(2, 1, 8);
    matrix.setValue(2, 2, 9);


    double determinant = matrix.Determinant();


    EXPECT_DOUBLE_EQ(determinant, 0);
}


TEST(S21MatrixTest, Determinant_1x1) {

    S21Matrix matrix(1, 1);


    matrix.setValue(0, 0, 100);



    double determinant = matrix.Determinant();


    EXPECT_DOUBLE_EQ(determinant, 100);
}



TEST(S21MatrixTest, CalcComplements) {
    // Test: Calculating the matrix of cofactors (complements) for a 3x3 matrix
    S21Matrix matrix(3, 3);
    matrix.setValue(0, 0, 1);
    matrix.setValue(0, 1, 2);
    matrix.setValue(0, 2, 3);
    matrix.setValue(1, 0, 0);
    matrix.setValue(1, 1, 4);
    matrix.setValue(1, 2, 2);
    matrix.setValue(2, 0, 5);
    matrix.setValue(2, 1, 2);
    matrix.setValue(2, 2, 1);



    S21Matrix res = matrix.CalcComplements();

    S21Matrix expected(3, 3);
    expected.setValue(0, 0, 0);
    expected.setValue(0, 1, 10);
    expected.setValue(0, 2, -20);

    expected.setValue(1, 0, 4);
    expected.setValue(1, 1, -14);
    expected.setValue(1, 2, 8);

    expected.setValue(2, 0, -8);
    expected.setValue(2, 1, -2);
    expected.setValue(2, 2, 4);


    // Check if the resulting matrix matches the expected matrix
    EXPECT_TRUE(res == expected);
}


TEST(S21MatrixTest, CalcComplements_1x1){
    S21Matrix matrix(1, 1);
    matrix.setValue(0,0,3);
    matrix =  matrix.CalcComplements();
    EXPECT_EQ(matrix.getValue(0,0),1);
}



TEST(S21MatrixTest, Inverse_matrix){
    S21Matrix test(3,3);

    test.setValue(0,0,2);
    test.setValue(0,1,5);
    test.setValue(0,2,7);
    test.setValue(1,0,6);
    test.setValue(1,1,3);
    test.setValue(1,2,4);
    test.setValue(2,0,5);
    test.setValue(2,1,-2);
    test.setValue(2,2,-3);


    S21Matrix res(3,3);
    res.setValue(0,0,1);
    res.setValue(0,1,-1);
    res.setValue(0,2,1);
    res.setValue(1,0,-38);
    res.setValue(1,1,41);
    res.setValue(1,2,-34);
    res.setValue(2,0,27);
    res.setValue(2,1,-29);
    res.setValue(2,2,24);

    test = test.InverseMatrix();

    EXPECT_EQ(test.EqMatrix(res), true);
}

TEST(S21MatrixTest, Inverse_matrix_det_zero) {
    S21Matrix test(3, 3);

    // Инициализация тестовой матрицы 2x2
    test.setValue(0, 0, 1);
    test.setValue(0, 1, 2);
    test.setValue(0, 2, 3);
    test.setValue(1, 0, 4);
    test.setValue(1, 1, 5);
    test.setValue(1, 2, 6);
    test.setValue(2, 0, 7);
    test.setValue(2, 1, 8);
    test.setValue(2, 2, 9);


    // Проверка равенства полученной и ожидаемой обратной матрицы
    EXPECT_THROW(test.InverseMatrix(), std::length_error);
}

TEST(S21MatrixTest, Inverse_matrix_additional) {
    S21Matrix test(2, 2);

    // Инициализация тестовой матрицы 2x2
    test.setValue(0, 0, 4);
    test.setValue(0, 1, 7);
    test.setValue(1, 0, 2);
    test.setValue(1, 1, 6);

    // Вычисление обратной матрицы
    S21Matrix m = test.InverseMatrix();

    // Ожидаемая обратная матрица
    S21Matrix expected(2, 2);
    expected.setValue(0, 0, 0.6);
    expected.setValue(0, 1, -0.7);
    expected.setValue(1, 0, -0.2);
    expected.setValue(1, 1, 0.4);

    // Проверка равенства полученной и ожидаемой обратной матрицы
    EXPECT_EQ(m.EqMatrix(expected), true);
}

TEST(S21MatrixTest,Valid_func_except){

    S21Matrix test(3,2);

    EXPECT_THROW(test.Valid_rows_cols_for_matrix(test), std::length_error);
    EXPECT_THROW(test.Valid_rows_cols(), std::length_error);
}


TEST(S21MatrixTest, AssignmentOperatorSelfAssignment) {
    S21Matrix matrix(2, 2);
    matrix.setValue(0, 0, 5);
    matrix.setValue(0, 1, 6);
    matrix.setValue(1, 0, 7);
    matrix.setValue(1, 1, 8);

    S21Matrix& refMatrix = matrix;
    matrix = refMatrix;


    EXPECT_EQ(matrix.getValue(0, 0), 5);
    EXPECT_EQ(matrix.getValue(0, 1), 6);
    EXPECT_EQ(matrix.getValue(1, 0), 7);
    EXPECT_EQ(matrix.getValue(1, 1), 8);
}


TEST(S21MatrixTest, OperatorPlusEqual) {
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

    matrix1 += matrix2;

    EXPECT_EQ(matrix1.getValue(0, 0), 6);
    EXPECT_EQ(matrix1.getValue(0, 1), 8);
    EXPECT_EQ(matrix1.getValue(1, 0), 10);
    EXPECT_EQ(matrix1.getValue(1, 1), 12);
}



TEST(S21MatrixTest, OperatorPlus) {
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

    S21Matrix result = matrix1 + matrix2;

    EXPECT_EQ(result.getValue(0, 0), 6);
    EXPECT_EQ(result.getValue(0, 1), 8);
    EXPECT_EQ(result.getValue(1, 0), 10);
    EXPECT_EQ(result.getValue(1, 1), 12);
}

TEST(S21MatrixTest, OperatorMultiplyScalar) {
    S21Matrix matrix(2, 2);
    matrix.setValue(0, 0, 2);
    matrix.setValue(0, 1, 4);
    matrix.setValue(1, 0, 6);
    matrix.setValue(1, 1, 8);

    double scalar = 3.0;
    S21Matrix result = matrix * scalar;

    EXPECT_EQ(result.getValue(0, 0), 6);
    EXPECT_EQ(result.getValue(0, 1), 12);
    EXPECT_EQ(result.getValue(1, 0), 18);
    EXPECT_EQ(result.getValue(1, 1), 24);
}
TEST(S21MatrixTest, OperatorMinusEqual) {
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

    matrix1 -= matrix2;

    EXPECT_EQ(matrix1.getValue(0, 0), 4);
    EXPECT_EQ(matrix1.getValue(0, 1), 4);
    EXPECT_EQ(matrix1.getValue(1, 0), 4);
    EXPECT_EQ(matrix1.getValue(1, 1), 4);
}


TEST(S21MatrixTest, OperatorMinus) {
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


    EXPECT_EQ(result.getValue(0, 0), 4);
    EXPECT_EQ(result.getValue(0, 1), 4);
    EXPECT_EQ(result.getValue(1, 0), 4);
    EXPECT_EQ(result.getValue(1, 1), 4);
}


TEST(S21MatrixTest, OperatorMultiplyEqual) {
    S21Matrix matrix1(2, 2);
    matrix1.setValue(0, 0, 1);
    matrix1.setValue(0, 1, 2);
    matrix1.setValue(1, 0, 3);
    matrix1.setValue(1, 1, 4);

    S21Matrix matrix2(2, 2);
    matrix2.setValue(0, 0, 2);
    matrix2.setValue(0, 1, 0);
    matrix2.setValue(1, 0, 1);
    matrix2.setValue(1, 1, 2);

    matrix1 *= matrix2;


    EXPECT_EQ(matrix1.getValue(0, 0), 4);
    EXPECT_EQ(matrix1.getValue(0, 1), 4);
    EXPECT_EQ(matrix1.getValue(1, 0), 10);
    EXPECT_EQ(matrix1.getValue(1, 1), 8);
}



TEST(S21MatrixTest, ConstOperatorParentheses) {
    const S21Matrix matrix(2, 2);
    // Установка значений матрицы для тестирования. Должны использовать неконстантную версию для установки.
    S21Matrix& nonConstMatrix = const_cast<S21Matrix&>(matrix);
    nonConstMatrix.setValue(0, 0, 1);
    nonConstMatrix.setValue(0, 1, 2);
    nonConstMatrix.setValue(1, 0, 3);
    nonConstMatrix.setValue(1, 1, 4);

    // Проверка возвращаемых значений
    EXPECT_EQ(matrix(0, 0), 1);
    EXPECT_EQ(matrix(0, 1), 2);
    EXPECT_EQ(matrix(1, 0), 3);
    EXPECT_EQ(matrix(1, 1), 4);

    // Проверка на выброс исключения при неверных индексах
    EXPECT_THROW(matrix(2, 2), std::out_of_range);
}


TEST(S21MatrixTest, NonConstOperatorParentheses) {
    S21Matrix matrix(2, 2);
    matrix.setValue(0, 0, 5);
    matrix.setValue(0, 1, 6);
    matrix.setValue(1, 0, 7);
    matrix.setValue(1, 1, 8);

    // Изменение значения через неконстантный оператор ()
    matrix(0, 0) = 10;

    // Проверка измененного значения
    EXPECT_EQ(matrix(0, 0), 10);
    EXPECT_EQ(matrix(0, 1), 6);
    EXPECT_EQ(matrix(1, 0), 7);
    EXPECT_EQ(matrix(1, 1), 8);

    // Проверка на выброс исключения при неверных индексах
    EXPECT_THROW(matrix(2, 2), std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
