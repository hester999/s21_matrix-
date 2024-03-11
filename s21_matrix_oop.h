
#ifndef S21_MATRIX__S21_MATRIX_OOP_H
#define S21_MATRIX__S21_MATRIX_OOP_H

#include <string>

const std::string invalid_matrix{"Invalid matrix"};
const std::string calc_error{"Calculation error"};

class S21Matrix {
private:
    // Attributes
    int rows_, cols_;         // Rows and columns
    double **matrix_;         // Pointer to the memory where the matrix is allocated

public:
    S21Matrix(); // консрукто
    S21Matrix(int rows, int columns); // консрукто  с параметрами
    S21Matrix(const S21Matrix &other); // консрукто копиорования
   // S21Matrix(S21Matrix &&other); // консрукто
    ~S21Matrix(); // деструктор



    bool EqMatrix(const S21Matrix &other);
    void SumMatrix(const S21Matrix &other);
    void SubMatrix(const S21Matrix &other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix &other);
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();

    void CreateMatrix(int rows, int columns);
    void FreeMatrix();

    void setCol(int cols);
    int getCols(){return cols_;};

    void setRows(int rows);
    int getRows(){return rows_;};

    double **getMatrix(){return matrix_;};


    void setValue(int row, int col, double value);
    double getValue(int row, int col) const;

    S21Matrix& operator+=(const S21Matrix &other);
    S21Matrix operator+(const S21Matrix &other);
    S21Matrix& operator-=(const S21Matrix &other);
    S21Matrix operator-(const S21Matrix &other);
    S21Matrix operator*=(const S21Matrix &other);
    S21Matrix operator*(const S21Matrix &other);
    S21Matrix operator*=(const double num);
    S21Matrix operator*(const double num);
    S21Matrix & operator=(const S21Matrix &other);
    bool operator==(const S21Matrix &other);
    double &operator()(int i, int j);
    double &operator()(int i, int j) const;



    void Valid_rows_cols(const S21Matrix &other);

};

#endif //S21_MATRIX__S21_MATRIX_OOP_H
