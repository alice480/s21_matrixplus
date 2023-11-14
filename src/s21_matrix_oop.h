#ifndef SRC_S21MATRIX_H_
#define SRC_S21MATRIX_H_

#include <cmath>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <utility>

class S21Matrix {
 private:
  // attributes
  int rows_, cols_;  // rows and columns attributes
  double **matrix_;  // pointer to the memory where the matrix will be allocated

  double **MatrixMemoryAllocation(int rows, int cols);
  void ChangeSize(int n_rows, int n_cols);
  void ClearMatrix();

 public:
  S21Matrix();                       // default constructor
  S21Matrix(int rows, int cols);     // parameterized constructor
  S21Matrix(const S21Matrix &copy);  // copy constructor
  S21Matrix(S21Matrix &&moved);      // move constructor
  ~S21Matrix();                      // destructor

  // operators overloads
  S21Matrix &operator=(const S21Matrix &other);  // assigning values of another
                                                 // matrix to a matrix
  bool operator==(const S21Matrix &other);  // checking for equality of matrices

  double operator()(int row, int col) const;  // index operator overload

  S21Matrix operator+(const S21Matrix &other);    // addition of two matrices
  S21Matrix &operator+=(const S21Matrix &other);  // assignment of addition

  S21Matrix operator-(
      const S21Matrix &other);  // subtracting one matrix from another
  S21Matrix &operator-=(const S21Matrix &other);  // assignment of subtracting

  void operator*(const S21Matrix &other);  // matrix multiplication
  void operator*(const double num);        // multiplying a matrix by a number

  S21Matrix &operator*=(
      const S21Matrix &other);  // assignment of multiplication
  S21Matrix &operator*=(const double num);

  // public methods
  bool EqMatrix(const S21Matrix &other) const noexcept;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() noexcept;
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix MinorMatrix(int rm_row, int rm_col);

  // getters
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  double GetValue(int row, int col) const;

  // setters
  void SetValue(int row, int col, double value);
  void SetRows(int rows);
  void SetCols(int cols);
};

#endif  // SRC_S21MATRIX_H_
