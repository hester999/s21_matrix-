#include <iostream>
#include "s21_matrix_oop.h"
#include <math.h>



/// construction and destruction
S21Matrix::S21Matrix() {
    rows_ = 0;
    cols_ = 0;
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

} // конструктор копирования, который вызывает конструктор с параметрами

S21Matrix::S21Matrix(S21Matrix &&other) : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}

/// construction and destruction end



/// Create and remove matrix functions
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
/// Create and remove matrix functions

/// the part for matrix expansion
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
/// end the part for matrix expansion



/// Get/Set functions for set and get private field
void S21Matrix::setValue(int row, int col, double value) {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
        matrix_[row][col] = value;
    } else {
        throw std::out_of_range("Index out of range");
    }
}

 double S21Matrix::getValue(int row, int col) const  {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
        return matrix_[row][col];
    } else {
        throw std::out_of_range("Index out of range");
    }
}
/// end of the block get/set functions



///Блок арифметики

void S21Matrix::SumMatrix(const S21Matrix &other) {
    Valid_rows_cols_for_matrix(other);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
//            matrix_[i][j] += other.matrix_[i][j];
            (*this)(i,j) += other(i,j);
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
    Valid_rows_cols_for_matrix(other);
    for(int i = 0; i< rows_; i++){
        for(int j =0;  j< cols_;j++){
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}


void S21Matrix::MulNumber(const double num)  {
    if(isinf(num) || isnan(num)){
        throw std::length_error(calc_error);
    }

    for(int i =0; i<rows_; i++){
        for (int j = 0; j<cols_; j++){
            (*this)(i,j) *= num;
        }
    }
}


void S21Matrix::MulMatrix(const S21Matrix &other) {
    Valid_rows_cols_for_matrix(other);

    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
//                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
                result(i,j) += (*this)(i,k) * other(k,j);
            }
        }
    }
    *this = result;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
    bool res = true;
    for(int i=0; i < rows_;i++){
        for(int j = 0; j<cols_; j++){
            if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) {
                res = false;
                break;
            }
        }
    }
    return  res;
}



S21Matrix  S21Matrix::Transpose(){

    S21Matrix res(cols_, rows_);

    for(auto i = 0; i < rows_;i++){
        for(auto j= 0; j<cols_;j++){
            res(j,i) = (*this)(i,j);
        }
    }

    return res;
}



double S21Matrix::Determinant() {
    double  res = 0;

    Valid_rows_cols();

    if(rows_ ==1 && cols_ == 1){
        res = (*this)(0,0);
    }else if(rows_ == 2 && cols_ ==2){
        res= ((*this)(0,0) * (*this)(1,1)) - ((*this)(0,1)*(*this)(1,0));
    }else{
        for(auto k =0; k<rows_;k++){
            S21Matrix minor(rows_ -1 , cols_ -1);
            for(auto  i = 1; i<rows_;i++){
                for(auto j = 0,col = 0; j<cols_;j++){
                    if(k==j){ continue;
                    }
                    minor.matrix_[i-1][col] = (*this)(i,j);
                    col++;
                }
            }

            double minor_result = minor.Determinant();
            res += pow(-1, k) * (*this)(0, k) * minor_result;
        }
    }
    return res;
}

S21Matrix S21Matrix::CalcComplements() {
    Valid_rows_cols();
    S21Matrix complements(rows_,cols_);

    if(rows_ ==1  && cols_ == 1){
        complements(0,0) = 1;
    }else{
        for(int i =0; i < rows_;i++){
            for(int k = 0; k< cols_;k++){
                S21Matrix minor(rows_-1,cols_-1);
                get_minor(minor,i,k);
                double temp = minor.Determinant();
                complements(i, k) = pow(-1, i + k) * temp;
            }
        }
    }

    return  complements;
}

void S21Matrix::get_minor(S21Matrix &minor_matrix, int remove_row, int remove_col) {
    int r = 0;
    for(int i = 0; i < rows_; i++){
        if(i == remove_row){
            continue;
        }
       int  c=0;
        for(int k=0; k<cols_;k++){
            if(remove_col == k){
                continue;
            }
            minor_matrix(r,c) = (*this)(i,k);
            c++;
        }
        r++;
    }
}


S21Matrix  S21Matrix::InverseMatrix(){
    Valid_rows_cols();
    S21Matrix res_matrix(rows_,cols_);
    double  det = Determinant();
    if(det == 0){
        throw std::length_error(calc_error);
    }
    res_matrix = CalcComplements();

    res_matrix = res_matrix.Transpose();
    res_matrix.MulNumber(1/det);
    return res_matrix;

}



/// Конец блока арифметики


/// Validation function
void S21Matrix::Valid_rows_cols_for_matrix(const S21Matrix &other) {
    if (cols_ != other.rows_) {
        throw std::length_error(calc_error);
    }
}



void S21Matrix::Valid_rows_cols(){

    if(rows_ != cols_){
        throw std::length_error(calc_error);
    }
}



/// operators

S21Matrix& S21Matrix::operator=(const S21Matrix &other) {
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


S21Matrix S21Matrix::operator*(const double num) {
    Valid_rows_cols();
    S21Matrix result =*this;
    result.MulNumber(num);
    return result;
}

S21Matrix& S21Matrix::operator*=(const double num) {
    Valid_rows_cols();
    MulNumber(num);
    return *this;
}



S21Matrix&  S21Matrix::operator-=(const S21Matrix &other) {
    this->SubMatrix(other);
    return *this;
}



S21Matrix& S21Matrix::operator*=(const S21Matrix &other){
    Valid_rows_cols_for_matrix(other);

    this->MulMatrix(other);

    return  *this;
}


S21Matrix S21Matrix::operator*(const S21Matrix &other){
    Valid_rows_cols_for_matrix(other);
    S21Matrix result =*this;
    result.MulMatrix(other);

    return  result;
}



S21Matrix  S21Matrix::operator-(const S21Matrix &other) {
    S21Matrix result = *this;
    result.SubMatrix(other);
    return result;

}

bool S21Matrix::operator==(const S21Matrix &other){
    bool res = this->EqMatrix(other);
    return  res;
}

const double& S21Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_[i][j];
}

double& S21Matrix::operator()(int i, int j) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_[i][j];
}


void S21Matrix::PrintMatrix(S21Matrix& matrix) {
    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.getCols(); ++j) {
            std::cout << matrix.getValue(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

