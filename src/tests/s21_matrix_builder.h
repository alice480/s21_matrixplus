#ifndef _SRC_S21_MATRIX_BUILDER_H_
#define _SRC_S21_MATRIX_BUILDER_H_

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "../s21_matrix_oop.h"

class VectorsMatrixBuilder {
 public:
  std::unique_ptr<S21Matrix> CreateMatrix(int rows, int cols);
  void FillMatrix(std::vector<double> values,
                  std::unique_ptr<S21Matrix> &matrix);
  void OutputMatrix(std::unique_ptr<S21Matrix> const &matrix);
};

#endif  // _SRC_S21_MATRIX_BUILDER_H_