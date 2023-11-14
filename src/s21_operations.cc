#include "s21_matrix_oop.h"

// OPERATIONS

// comparison of two matrices by dimension and cell values
bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  bool equality = (rows_ == other.rows_ && cols_ == other.cols_);
  for (auto i = 0; i < rows_; ++i)
    for (auto j = 0; j < cols_ && equality; ++j)
      equality = (matrix_[i][j] == other.matrix_[i][j]);
  return equality;
}

// matrix addition
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Matrices should have the same size");
  for (auto i = 0; i < rows_; ++i)
    for (auto j = 0; j < cols_; ++j) matrix_[i][j] += other.matrix_[i][j];
}

// matrix subtraction
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Matrices should have the same size");
  for (auto i = 0; i < rows_; ++i)
    for (auto j = 0; j < cols_; ++j) matrix_[i][j] -= other.matrix_[i][j];
}

// multiplying matrix values by a number
void S21Matrix::MulNumber(const double num) noexcept {
  for (auto i = 0; i < rows_; ++i)
    for (auto j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

// multiplying the matrix by the transmitted matrix
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "The number of columns of the matrix1 must be "
        "equal to the number of rows of the matrix2");
  // the dimension of the resulting matrix is [rows_, other.cols_]
  double **res_matr = MatrixMemoryAllocation(rows_, other.cols_);
  for (auto row = 0; row < rows_; ++row)
    for (auto col = 0; col < other.cols_; ++col)
      for (auto k = 0; k < cols_; ++k)
        res_matr[row][col] += matrix_[row][k] * other.matrix_[k][col];
  ClearMatrix();
  matrix_ = res_matr;
  cols_ = other.cols_;
}

// creates a new transposed matrix from the current one and returns it
S21Matrix S21Matrix::Transpose() noexcept {
  S21Matrix result = S21Matrix(cols_, rows_);
  for (auto i = 0; i < rows_; ++i)
    for (auto j = 0; j < cols_; ++j) result.matrix_[j][i] = matrix_[i][j];
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix calc_mx = S21Matrix(rows_, cols_);
  for (auto row = 0; row < rows_; ++row)
    for (auto col = 0; col < cols_; ++col)
      calc_mx.matrix_[row][col] =
          std::pow(-1, row + col) * MinorMatrix(row, col).Determinant();
  return calc_mx;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) throw std::invalid_argument("The matrix is not square");
  if (rows_ == 1) return matrix_[0][0];
  if (rows_ == 2)
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  // calculation of the determinant of the order >=(3, 3)
  double det = 0;
  for (auto col = 0; col < cols_; ++col) {
    double mnog = std::pow(-1, col) * matrix_[0][col];
    S21Matrix new_mx = MinorMatrix(0, col);
    det += mnog * new_mx.Determinant();
  }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (!det) throw std::invalid_argument("The determinant of the matrix is 0");
  S21Matrix inverse_mx = CalcComplements().Transpose();
  inverse_mx.MulNumber(1 / det);
  return inverse_mx;
}

S21Matrix S21Matrix::MinorMatrix(int rm_row, int rm_col) {
  if (rows_ != cols_) throw std::invalid_argument("The matrix is not square");

  // an N-1 order matrix for computing a minor
  S21Matrix minor_mx = S21Matrix(rows_ - 1, cols_ - 1);
  // deleting a row
  for (auto minor_i = 0, orig_i = 0; orig_i < rows_; ++minor_i, ++orig_i) {
    (minor_i == rm_row) ? ++orig_i : orig_i;
    // deleting a column
    for (auto minor_j = 0, orig_j = 0; orig_j < cols_; ++minor_j, ++orig_j) {
      (minor_j == rm_col) ? ++orig_j : orig_j;
      // writing a value from the original matrix to the minor matrix
      if (orig_i < rows_ && orig_j < cols_)
        minor_mx.matrix_[minor_i][minor_j] = matrix_[orig_i][orig_j];
    }
  }
  return minor_mx;
}
