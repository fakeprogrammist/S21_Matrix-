#ifndef CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

#define EPS 1e-7

class S21Matrix {
 public:

  S21Matrix() = default;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator=(S21Matrix&& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  bool operator==(const S21Matrix& other) const;
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;

 private:
  int rows_ = 0, cols_ = 0;
  double** matrix_ = nullptr;
  void RemoveMatrix();
  void SetNull();
  void CopyMatrix(const S21Matrix& other);
  void CreateMatrix();
  void CreateMinor(int i, int j, const S21Matrix& minor) const;
  void ExceptionMatrixDoesntExist() const;
  void ExceptionMatrixIsNotSquare() const;
  void ExceptionMatrixDoesntExist(const S21Matrix& other) const;
  void ExceptionDifferentDimensions(const S21Matrix& other) const;
  void ExceptionDifferentDimensionsForMul(const S21Matrix& other) const;
  void ExceptionOutOfRange(int i, int j) const;
  void ExceptionDeterminant(double determinant) const;
};

#endif  // CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H