#include "s21_matrix_oop.h"

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.SetNull();
}

S21Matrix::~S21Matrix() { RemoveMatrix(); }

void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::RemoveMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  SetNull();
}

void S21Matrix::SetRows(int rows) {
  S21Matrix tempM(rows, cols_);
  // int x = 0; if (rows_ < rows) x = rows_; else x = rows;
  for (int i = 0; i < ((rows_ < rows) ? rows_ : rows); i++) {
    for (int j = 0; j < cols_; j++) {
      tempM.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(tempM);
}

void S21Matrix::SetCols(int cols) {
  S21Matrix tempM(rows_, cols);
  // int x = 0; if (cols_ < cols) x = cols_; else x = cols;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < ((cols_ < cols) ? cols_ : cols); j++) {
      tempM.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(tempM);
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  if (this != &other) {
    CreateMatrix();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SetNull() {
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix tempM(*this);
  tempM.SumMatrix(other);
  return tempM;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix tempM(*this);
  tempM.SubMatrix(other);
  return tempM;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix tempM(*this);
  tempM.MulMatrix(other);
  return tempM;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix tempM(*this);
  tempM.MulNumber(num);
  return tempM;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  S21Matrix tempM(other);
  *this = std::move(tempM);
  return *this;
}

S21Matrix S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    RemoveMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.SetNull();
  }
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

double &S21Matrix::operator()(int i, int j) {
  ExceptionOutOfRange(i, j);
  return matrix_[i][j];
}

const double &S21Matrix::operator()(int i, int j) const {
  ExceptionOutOfRange(i, j);
  return matrix_[i][j];
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  ExceptionMatrixDoesntExist(other);
  ExceptionDifferentDimensions(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}
void S21Matrix::SubMatrix(const S21Matrix &other) {
  ExceptionMatrixDoesntExist(other);
  ExceptionDifferentDimensions(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  ExceptionMatrixDoesntExist();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  ExceptionMatrixDoesntExist(other);
  ExceptionDifferentDimensionsForMul(other);
  S21Matrix tempM(rows_, other.cols_);
  for (int i = 0; i < tempM.rows_; i++) {
    for (int j = 0; j < tempM.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        tempM.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(tempM);
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool result = true;
  ExceptionMatrixDoesntExist(other);
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  }
  for (int i = 0; i < rows_ && result == true; i++) {
    for (int j = 0; j < cols_ && result == true; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
        result = false;
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::Transpose() const {
  ExceptionMatrixDoesntExist();
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  double result = 0.0;
  ExceptionMatrixIsNotSquare();
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix minor(rows_ - 1, cols_ - 1);
    for (int j = 0; j < cols_; j++) {
      CreateMinor(0, j, minor);
      result += pow(-1.0, j) * minor.Determinant() * matrix_[0][j];
    }
  }
  return result;
}

void S21Matrix::CreateMinor(int i, int j, const S21Matrix &minor) const {
  int minor_i = 0;
  int minor_j = 0;
  for (int current_i = 0; current_i < rows_; current_i++) {
    for (int current_j = 0; current_j < cols_; current_j++) {
      if (current_j != j && current_i != i) {
        minor.matrix_[minor_i][minor_j] = matrix_[current_i][current_j];
        minor_j++;
        if (minor_j == cols_ - 1) {
          minor_i++;
          minor_j = 0;
        }
      }
    }
  }
}

S21Matrix S21Matrix::CalcComplements() const {
  ExceptionMatrixDoesntExist();
  ExceptionMatrixIsNotSquare();
  S21Matrix result(rows_, cols_);
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      CreateMinor(i, j, minor);
      result.matrix_[i][j] = pow(-1, (j + i) + 2) * minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  ExceptionMatrixDoesntExist();
  ExceptionMatrixIsNotSquare();
  double determinant = Determinant();
  ExceptionDeterminant(determinant);
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    result = CalcComplements().Transpose();
    result.MulNumber(1 / determinant);
  }
  return result;
}

void S21Matrix::ExceptionMatrixDoesntExist() const {
  if (matrix_ == nullptr) {
    throw std::length_error("Matrix doesn't exist");
  }
}

void S21Matrix::ExceptionMatrixIsNotSquare() const {
  if (rows_ != cols_) {
    throw std::length_error("Matrix is not square");
  }
}

void S21Matrix::ExceptionMatrixDoesntExist(const S21Matrix &other) const {
  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    throw std::length_error("Matrix doesn't exist");
  }
}

void S21Matrix::ExceptionDifferentDimensions(const S21Matrix &other) const {
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    throw std::length_error("Different dimensions");
  }
}

void S21Matrix::ExceptionDifferentDimensionsForMul(
    const S21Matrix &other) const {
  if (cols_ != other.rows_) {
    throw std::length_error("Different dimensions for mul");
  }
}

void S21Matrix::ExceptionOutOfRange(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::length_error("Out of range");
  }
}

void S21Matrix::ExceptionDeterminant(double determinant) const {
  if (fabs(determinant) < EPS) {
    throw std::length_error("Matrix determinant is 0");
  }
}
