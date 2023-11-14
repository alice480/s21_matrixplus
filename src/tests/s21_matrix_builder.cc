#include "s21_matrix_builder.h"

std::unique_ptr<S21Matrix> VectorsMatrixBuilder::CreateMatrix(int rows,
                                                              int cols) {
  return {std::make_unique<S21Matrix>(S21Matrix(rows, cols))};
}

// values: vector of matrix values
void VectorsMatrixBuilder::FillMatrix(std::vector<double> values,
                                      std::unique_ptr<S21Matrix> &matrix) {
  auto rows = matrix->GetRows();
  auto cols = matrix->GetCols();
  for (auto i = 0; i < rows; i++)
    for (auto j = 0; j < cols; j++)
      matrix->SetValue(i, j, values[i * cols + j]);
}

// mx_index: the index of the matrix in the vector of objects S21Matrix
void VectorsMatrixBuilder::OutputMatrix(
    std::unique_ptr<S21Matrix> const &matrix) {
  auto rows = matrix->GetRows();
  auto cols = matrix->GetCols();
  for (auto i = 0; i < rows; ++i) {
    for (auto j = 0; j < cols; ++j) {
      std::cout << matrix->GetValue(i, j);
      if (j != cols) std::cout << "\t";
    }
    std::cout << "\n";
  }
}
