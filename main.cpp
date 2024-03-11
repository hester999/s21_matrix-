#include <iostream>
#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
    rows_ = 1;
    cols_ = 1;
    matrix_ = nullptr;
} // конструктор по умолчанию
S21Matrix::~S21Matrix() {
    FreeMatrix();
} // деструктор

S21Matrix::S21Matrix(int rows, int columns) {
    CreateMatrix(rows,columns);
} // конструктор



S21Matrix::S21Matrix(const S21Matrix &other): S21Matrix(other.rows_,other.cols_) {

    for(int i =0; i< rows_; i++){
        for(int j=0; j<cols_; j++){
            matrix_[i][j] = other.matrix_[i][j];
        }
    }

}

void S21Matrix::CreateMatrix(int rows, int columns) {

    if(rows < 1 || columns < 1){
        throw std::length_error(invalid_matrix);
    }
    rows_ = rows;
    cols_ = columns;

    matrix_ = new double *[rows]();

    for(int i =0; i<rows; i++){
        matrix_[i]  = new double [columns]();
    }
}


void S21Matrix::FreeMatrix() {
    if (matrix_ != nullptr) {
        for (int i = 0; i < rows_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
    }
    rows_ = 0;
    cols_ = 0;
}



void S21Matrix::setRows(int rows) {
    if(rows<1){
        throw std::length_error(invalid_matrix);
    }

    if(rows != rows_){
        S21Matrix newMatrix(rows,cols_);
        int min_count_rows =  rows_ < rows ? rows_ : rows;

        for(int i = 0; i< min_count_rows; i++){
            for(int j = 0; j< cols_;j++){
                newMatrix.matrix_[i][j] = matrix_[i][j];
            }
        }
        *this = newMatrix;
    }
}

void S21Matrix::setCol(int cols) {
    if(cols < 1){
        throw std::length_error(invalid_matrix);
    }
    if(cols != cols_){
        S21Matrix newMatrix(rows_,cols);
        int min_count_cols =  cols_ < cols ? cols_ : cols;

        for(int i = 0; i< rows_; i++){
            for(int j = 0; j< min_count_cols;j++){
                newMatrix.matrix_[i][j] = matrix_[i][j];
            }
        }
        *this = newMatrix;
    }
}


void S21Matrix::setValue(int row, int col, double value) {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
        matrix_[row][col] = value;
    } else {
        throw std::out_of_range("Index out of range");
    }
}

double S21Matrix::getValue(int row, int col) const {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
        return matrix_[row][col];
    } else {
        throw std::out_of_range("Index out of range");
    }
}






void S21Matrix::SumMatrix(const S21Matrix &other) {
    Valid_rows_cols(other);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
    Valid_rows_cols(other);
    for(int i = 0; i< rows_; i++){
        for(int j =0;  j< cols_;j++){
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void S21Matrix::Valid_rows_cols(const S21Matrix &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::length_error(calc_error);
    }
}

S21Matrix & S21Matrix::operator=(const S21Matrix &other) {
    if (this == &other) {
        return *this;
    }
    this->FreeMatrix();

    this->CreateMatrix(other.rows_,other.cols_);

    for(int i =0; i < rows_;i++){
        for(int j=0; j< cols_;j++){
            matrix_[i][j] = other.matrix_[i][j];
        }
    }

    return *this;
}


S21Matrix&  S21Matrix::operator+=(const S21Matrix &other) {

    SumMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
    S21Matrix result = *this;
    result.SumMatrix(other);
    return result;
}




S21Matrix&  S21Matrix::operator-=(const S21Matrix &other) {
    this->SubMatrix(other);
    return *this;
}

S21Matrix  S21Matrix::operator-(const S21Matrix &other) {
    S21Matrix result = *this;
    result.SumMatrix(other);
    return result;

}



int main() {
    S21Matrix matrix1 (2, 2);
//    S21Matrix matrix1 (2, 2);
    matrix1.setValue(0, 0, 1);
    matrix1. setValue(0, 1, 2);
    matrix1.setValue(1, 0, 3);
    matrix1.setValue(1, 1, 4);

    S21Matrix matrix2 (2, 2);
    matrix2.setValue(0, 0, 5);
    matrix2.setValue(0, 1, 6);
    matrix2.setValue(1, 0, 7);
    matrix2.setValue(1, 1, 8);

    S21Matrix matrix3 = matrix1 + matrix2;;
//    matrix3 = matrix1+matrix2;
//    matrix3 = *matrix1 + *matrix2;
    std::cout << "Resulting Matrix:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << matrix3.getValue(i, j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}