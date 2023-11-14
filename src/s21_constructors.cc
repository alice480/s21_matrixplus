#include "s21_matrix_oop.h"

// CONSTRUCTORS

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = MatrixMemoryAllocation(rows_, cols_);
}

// parameterized constructor
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1)
    throw std::invalid_argument(
        "The number of rows and columns must be greater than 1");
  matrix_ = MatrixMemoryAllocation(rows, cols);
}

// copy cnstructor
S21Matrix::S21Matrix(const S21Matrix &copy)
    : rows_(copy.rows_), cols_(copy.cols_) {
  matrix_ = MatrixMemoryAllocation(rows_, cols_);
  for (auto i = 0; i < rows_; ++i)
    std::memcpy(matrix_[i], copy.matrix_[i], copy.cols_ * sizeof(double));
}

// move cnstructor
S21Matrix::S21Matrix(S21Matrix &&moved)
    : rows_(moved.rows_), cols_(moved.cols_), matrix_(moved.matrix_) {
  moved.matrix_ = nullptr;
  moved.rows_ = 0;
  moved.cols_ = 0;
}

// destructor
S21Matrix::~S21Matrix() {
  ClearMatrix();
  rows_ = 0;
  cols_ = 0;
}