#ifndef S21_MATRIX_OOP_H
# define S21_MATRIX_OOP_H

#include <cmath>

class S21Matrix {
private:

// Attributes
    int rows_, cols_;                                           // Rows and columns
    double **matrix_;                                           // Pointer to the memory the matrix is allocated

    bool EqMatrix(const S21Matrix &other);
    void CreateMatrix();
    void ExceptionNulMatrix(const S21Matrix matrix);
    void ExceptionOMatrix(const S21Matrix matrix);
    void ExceptionSizeMatrix(const S21Matrix other);
    void SubMatrix(const S21Matrix &other);
    void SumMatrix(const S21Matrix &other);
    // void MulMatrix(const S21Matrix &other);
    void MulNumber(const double num);
    void RemoveMatrix();
    void CopyMatrix(const S21Matrix &other);

    void SetNull();

    S21Matrix Transpose();

    double Determinant();
//    S21Matrix CalcComplements();
//
//    S21Matrix InverseMatrix();


public:

    S21Matrix();                                                    // Default constructor
    S21Matrix(int rows, int cols);                                  // Constructor which takes rows and cols
    S21Matrix(const S21Matrix &other);                              // Copy constructor
    S21Matrix(S21Matrix &&other) noexcept;                         // Moving constructor
    ~S21Matrix();                                                   // Destructor

};

#endif