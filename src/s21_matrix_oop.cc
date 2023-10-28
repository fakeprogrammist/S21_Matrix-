#include <stdexcept>
#include "s21_matrix_oop.h"

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    CreateMatrix(); 
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
    ExceptionSizeMatrix(other);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if ((*this).matrix_[i] != other.matrix_[i] || (*this).matrix_[j] != other.matrix_[j])
                return false;
        }
    }
    return true;
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
    ExceptionSizeMatrix(other);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            (*this).matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void S21Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            (*this).matrix_[i][j] *= num;
        }
    }
}

// void S21Matrix::MulMatrix(const S21Matrix &other) {
//     ExceptionSizeMatrix(other);
//     ExceptionOMatrix(other);
//     S21Matrix tempM((*this).rows_, other.cols_);
//     for (int i = 0; i < tempM.rows_; i++) {
//         for (int j = 0; j < tempM.cols_; j++) {
//             for (int k = 0; k < cols_; k++) {
//                 tempM.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
//             }
//         }
//     }
//     *this = std::move(tempM);
    
// }

//
S21Matrix S21Matrix::Transpose() {
    
   return S21Matrix();
}
//
//S21Matrix S21Matrix::CalcComplements() {
//    return S21Matrix();
//}
//
//S21Matrix S21Matrix::InverseMatrix() {
//    return S21Matrix();
//}
double S21Matrix::Determinant() {
    return 0;
}

S21Matrix::~S21Matrix() {
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
    ExceptionSizeMatrix(other);
    ExceptionNulMatrix(other);
    for (int i = 0; i < (*this).rows_; ++i) {
        for (int j = 0; j < (*this).cols_; ++j) {
            (*this).matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(const S21Matrix &other) {

}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {

}

void S21Matrix::ExceptionSizeMatrix(const S21Matrix other) {
    if (other.cols_ != (*this).cols_ || other.rows_ != (*this).rows_)
        throw std::length_error("Different Dimensions");
}

void S21Matrix::ExceptionNulMatrix(const S21Matrix matrix) {
    if (matrix.cols_ <= 0 && matrix.rows_ <= 0)
        throw std::length_error("Matrix is empty");
}

void S21Matrix::ExceptionOMatrix(const S21Matrix matrix) {
    for (int i = 0; i < matrix.rows_; i++) {
        for (int j = 0; j < matrix.cols_; j++) {
            if (matrix.matrix_[i][j] != 0)
                continue;
            else
                return;
        }
    }
    throw std::length_error("Matrix only have 0 digits");
}

S21Matrix S21Matrix::Transpose() {
    return S21Matrix();
}

void S21Matrix::RemoveMatrix() {
    for (int i = 0; i < rows_; ++i) {
        delete[] matrix_[i];
    }
    delete[] matrix_;
    SetNull();
}

void S21Matrix::SetNull() {
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
}

void S21Matrix::CreateMatrix(){
    matrix_ = new double*[rows_]();
    for (size_t i = 0; i < rows_; i++)
    {
        (*this).matrix_[i] = new double[cols_]();
    }
    
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
    if (this != &other){
        CreateMatrix();
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                (*this).matrix_[i][j] = other.matrix_[i][j];
            }
        }
    }
}
