#include "s21_matrix_oop.h"

// AUXILIARY METHODS

// allocation of space for double arrays
// input: matrix dimension values
double **S21Matrix::MatrixMemoryAllocation(int rows, int cols) {
  double **buf_mx = new double *[rows]();
  for (int i = 0; i < rows; ++i) buf_mx[i] = new double[cols]();
  return buf_mx;
}

// changing the size of the matrix
// when changing the value of the rows_ and cols fields_
// input: new values of <rows_> <cols_>
void S21Matrix::ChangeSize(int n_rows, int n_cols) {
  double **buf_mx = MatrixMemoryAllocation(n_rows, n_cols);
  auto rows_count = std::min(rows_, n_rows);
  auto cols_count = std::min(cols_, n_cols);
  for (auto i = 0; i < rows_count; ++i)
    for (auto j = 0; j < cols_count; ++j) buf_mx[i][j] = matrix_[i][j];
  ClearMatrix();
  matrix_ = buf_mx;
  buf_mx = nullptr;
}

// freeing the matrix memory
// releasing the pointer to the matrix
void S21Matrix::ClearMatrix() {
  if (matrix_) {
    for (auto i = 0; i < rows_; ++i) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

// ACCESSORS

// returns the value of the private attribute rows_
int S21Matrix::GetRows() const noexcept { return rows_; }

// returns the value of the private attribute cols_
int S21Matrix::GetCols() const noexcept { return cols_; }

double S21Matrix::GetValue(int row, int col) const {
  if (row < 0 || rows_ <= row)
    throw std::out_of_range("The row index is incorrect");
  if (col < 0 || cols_ <= col)
    throw std::out_of_range("The column index is incorrect");
  return matrix_[row][col];
}

// MUTATORS

// recording the value at the address of the matrix cell
void S21Matrix::SetValue(int row, int col, double value) {
  if (row < 0 || col < 0)
    throw std::out_of_range("Index values must be greater than 0");
  if (rows_ <= row || cols_ <= col)
    throw std::out_of_range("The index exceeds the dimension of the matrix");
  matrix_[row][col] = value;
}

void S21Matrix::SetRows(int rows) {
  if (rows <= 0)
    throw std::out_of_range(
        "Incorrect input, rows value must be greater than 0");
  if (rows_ != rows) {
    ChangeSize(rows, cols_);
    rows_ = rows;
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0)
    throw std::out_of_range(
        "Incorrect input, cols value must be greater than 0");
  if (cols_ != cols) {
    ChangeSize(rows_, cols);
    cols_ = cols;
  }
}