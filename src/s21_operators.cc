#include "s21_matrix_oop.h"

// OPERATOR OVERLOADING

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  ClearMatrix();
  matrix_ = MatrixMemoryAllocation(other.rows_, other.cols_);
  rows_ = other.rows_;
  cols_ = other.cols_;
  for (auto i = 0; i < rows_; ++i)
    std::memcpy(matrix_[i], other.matrix_[i], other.cols_ * sizeof(double));
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res = S21Matrix(*this);  // creating result matrix
  res.SumMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res = S21Matrix(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

void S21Matrix::operator*(const S21Matrix &other) { MulMatrix(other); }

void S21Matrix::operator*(const double num) { MulNumber(num); }

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

// index operator overload
double S21Matrix::operator()(int row, int col) const {
  return GetValue(row, col);
}