#include "s21_tests.h"

TEST(ConstructorsTests, default_constructor) {
  // ARRANGE
  S21Matrix *A;
  // ACT
  A = new S21Matrix();
  int rows = A->GetRows();
  int cols = A->GetCols();
  // ASSERT
  ASSERT_NE(A, nullptr);
  EXPECT_EQ(rows, 3);
  EXPECT_EQ(cols, 3);

  delete A;
}

TEST(ConstructorsTests, parameterized_constructor) {
  // ARRANGE
  S21Matrix *A;
  // ACT
  A = new S21Matrix(5, 5);
  int rows = A->GetRows();
  int cols = A->GetCols();
  // ASSERT
  ASSERT_NE(A, nullptr);
  EXPECT_EQ(rows, 5);
  EXPECT_EQ(cols, 5);

  delete A;
}

TEST(ConstructorsTests, parameterized_constructor_throw) {
  // ASSERT
  ASSERT_THROW(S21Matrix(2, -7), std::invalid_argument);
  ASSERT_THROW(S21Matrix(0, 4), std::invalid_argument);
}

TEST(ConstructorsTests, copy_constructor) {
  // ARRANGE
  S21Matrix *A, *B;
  // ACT
  A = new S21Matrix(5, 5);
  B = new S21Matrix(*A);
  int a_rows = A->GetRows();
  int a_cols = A->GetCols();
  int b_rows = B->GetRows();
  int b_cols = B->GetCols();
  // ASSERT
  ASSERT_NE(A, nullptr);
  ASSERT_NE(B, nullptr);
  EXPECT_EQ(a_cols, 5);
  EXPECT_EQ(a_rows, 5);
  EXPECT_EQ(b_rows, 5);
  EXPECT_EQ(b_cols, 5);

  delete A;
  delete B;
}

TEST(ConstructorsTests, move_constructor) {
  // ARRANGE
  S21Matrix *A, *B;
  // ACT
  A = new S21Matrix(5, 5);
  B = new S21Matrix(std::move(*A));
  int a_rows = A->GetRows();
  int a_cols = A->GetCols();
  int b_rows = B->GetRows();
  int b_cols = B->GetCols();
  // ASSERT
  ASSERT_NE(A, nullptr);
  ASSERT_NE(B, nullptr);
  EXPECT_EQ(a_cols, 0);
  EXPECT_EQ(a_rows, 0);
  EXPECT_EQ(b_rows, 5);
  EXPECT_EQ(b_cols, 5);

  delete A;
  delete B;
}

TEST(OperationsTests, equal_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4, 5, 6, 7, 10, 9};
  std::vector<double> vec2{10, 9, 8, 7, 6, 5, 4, 3, 2};
  std::vector<double> vec3{1, 2, 3, 4};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};
  // creating a matrix A
  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 3);
  // filling the matrix A with values from the vector
  builder->FillMatrix(vec1, A);
  // creating a matrix B
  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(3, 3);
  // filling the matrix A with values from the vector
  builder->FillMatrix(vec2, B);
  // Creating a matrix C
  std::unique_ptr<S21Matrix> C = builder->CreateMatrix(2, 2);

  // ACT and ASSERT

  // identical in dimension and values
  // expected output: 1
  EXPECT_EQ(A->EqMatrix(*A), 1);

  // the same in dimension, but different in values
  // expected output: 0
  EXPECT_EQ(A->EqMatrix(*B), 0);

  // different in dimension
  EXPECT_EQ(A->EqMatrix(*C), 0);

  A.reset();
  B.reset();
  C.reset();
  builder.reset();
}

TEST(OperationsTests, sum_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4, 5, 6, 7, 9, 10};
  std::vector<double> vec2{2, 4, 6, 8, 10, 12, 14, 18, 20};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  // creating a matrix A
  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 3);
  // filling the matrix A with values from the vector
  builder->FillMatrix(vec1, A);
  // creating a matrix B
  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(3, 3);
  // filling the matrix A with values from the vector
  builder->FillMatrix(vec2, B);
  // Creating a matrix C
  std::unique_ptr<S21Matrix> C = builder->CreateMatrix(2, 2);

  // ACT
  A->SumMatrix(*A.get());

  // ASSERT
  EXPECT_EQ(A->EqMatrix(*B.get()), 1);
  EXPECT_THROW(A->SumMatrix(*C.get()), std::invalid_argument);

  A.reset();
  B.reset();
  C.reset();
  builder.reset();
}

TEST(OperationsTests, sub_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4, 5, 6, 7, 9, 10};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  // creating a matrix A
  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 3);
  // filling the matrix A with values from the vector
  builder->FillMatrix(vec1, A);
  // creating a matrix B filled with zeros by default
  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(3, 3);
  // Creating a matrix C
  std::unique_ptr<S21Matrix> C = builder->CreateMatrix(2, 2);

  // ACT
  A->SubMatrix(*A.get());

  // ASSERT
  EXPECT_EQ(A->EqMatrix(*B.get()), 1);
  EXPECT_THROW(A->SubMatrix(*C.get()), std::invalid_argument);

  A.reset();
  B.reset();
  C.reset();
  builder.reset();
}

TEST(OperationsTests, mul_number_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<double> vec2{5, 10, 15, 20, 25, 30, 35, 40, 45};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  // creating a matrix A
  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 3);
  // filling the matrix A with values from the vector
  builder->FillMatrix(vec1, A);
  // creating a matrix B filled with zeros by default
  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(3, 3);
  builder->FillMatrix(vec2, B);

  // ACT
  A->MulNumber(5);

  // ASSERT
  EXPECT_EQ(A->EqMatrix(*B.get()), 1);

  A.reset();
  B.reset();
  builder.reset();
}

TEST(OperationsTests, mult_matrix_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4, 5, 6};
  std::vector<double> vec2{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<double> res{11, 14, 17, 20, 23, 30, 37, 44, 35, 46, 57, 68};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 2);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(2, 4);
  builder->FillMatrix(vec2, B);

  std::unique_ptr<S21Matrix> C = builder->CreateMatrix(3, 4);
  builder->FillMatrix(res, C);

  // ACT
  A->MulMatrix(*B.get());

  // ASSERT

  // multiplication of matrices suitable in dimension
  // expected result: matrix size (3, 4) with values of the res vector
  EXPECT_EQ(A->EqMatrix(*C.get()), 1);

  // multiplication of matrices of incorrect dimension
  EXPECT_THROW(A->MulMatrix(*A.get()), std::invalid_argument);

  A.reset();
  B.reset();
  C.reset();
  builder.reset();
}

TEST(OperationsTests, transpose_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4, 5, 6};
  std::vector<double> res{1, 3, 5, 2, 4, 6};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 2);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(2, 3);
  builder->FillMatrix(res, B);

  // ACT
  S21Matrix C = A->Transpose();

  // ASSERT
  EXPECT_EQ(C.EqMatrix(*B.get()), 1);

  A.reset();
  B.reset();
  builder.reset();
}

TEST(OperationsTests, calc_components_test) {
  // ARRANGE
  std::vector<double> vec1{1, 51, 9, 13, 4, 5,  6, 24,
                           7, 10, 9, 31, 8, 17, 3, 6};
  std::vector<double> res{-345, 144,   98,   3,     -615, 1152, -10546, 2829,
                          435,  -1008, 8554, -2001, 960,  288,  -2224,  336};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(4, 4);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(4, 4);
  builder->FillMatrix(res, B);

  // ACT
  std::unique_ptr<S21Matrix> D =
      std::make_unique<S21Matrix>(A->CalcComplements());

  // ASSERT
  EXPECT_EQ(D->EqMatrix(*B.get()), 1);

  A.reset();
  B.reset();
  D.reset();
  builder.reset();
}

TEST(OperationsTests, inverse_matrix_test) {
  // ARRANGE
  std::vector<double> vec1{2, 5, 7, 6, 3, 4, 5, -2, -3};
  std::vector<double> res{1, -1, 1, -38, 41, -34, 27, -29, 24};
  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 3);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(3, 3);
  builder->FillMatrix(res, B);

  // ACT
  std::unique_ptr<S21Matrix> D =
      std::make_unique<S21Matrix>(A->InverseMatrix());

  // ASSERT
  EXPECT_EQ(D->EqMatrix(*B.get()), 1);

  A.reset();
  B.reset();
  D.reset();
  builder.reset();
}

TEST(MutatorsTests, set_row_test) {
  // ARRANGE
  std::vector<double> vec1{1, 51, 9, 13, 4, 5,  6, 24,
                           7, 10, 9, 31, 8, 17, 3, 6};
  std::vector<double> res{1, 51, 9, 13, 4, 5, 6, 24, 7, 10, 9, 31};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(4, 4);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(3, 4);
  builder->FillMatrix(res, B);

  // ACT
  A->SetRows(3);

  // ASSERT
  EXPECT_EQ(A->EqMatrix(*B.get()), 1);
  // impossible number of rows
  EXPECT_THROW(A->SetRows(-1), std::out_of_range);

  A.reset();
  B.reset();
  builder.reset();
}

TEST(MutatorsTests, set_cols_test) {
  // ARRANGE
  std::vector<double> vec1{1, 51, 9, 13, 4, 5,  6, 24,
                           7, 10, 9, 31, 8, 17, 3, 6};
  std::vector<double> res{1, 51, 9, 4, 5, 6, 7, 10, 9, 8, 17, 3};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(4, 4);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(4, 3);
  builder->FillMatrix(res, B);

  // ACT
  A->SetCols(3);

  // ASSERT
  EXPECT_EQ(A->EqMatrix(*B.get()), 1);
  // impossible number of rows
  EXPECT_THROW(A->SetCols(0), std::out_of_range);

  A.reset();
  B.reset();
  builder.reset();
}

TEST(MutatorsTests, set_value_test) {
  // ARRANGE
  std::vector<double> vec1{1, 51, 9, 13, 4, 5,  6, 24,
                           7, 10, 9, 31, 8, 17, 3, 6};
  std::vector<double> res{1, 1000, 9, 13, 4, 5,  6, 24,
                          7, 10,   9, 31, 8, 17, 3, 1000};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(4, 4);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(4, 4);
  builder->FillMatrix(res, B);

  // ACT
  A->SetValue(0, 1, 1000);
  A->SetValue(3, 3, 1000);

  // ASSERT
  EXPECT_EQ(A->EqMatrix(*B.get()), 1);
  // impossible number of rows
  EXPECT_THROW(A->SetValue(-1, 2, 200), std::out_of_range);
  EXPECT_THROW(A->SetValue(2, -5, 200), std::out_of_range);
  EXPECT_THROW(A->SetValue(2, 4, 200), std::out_of_range);
  EXPECT_THROW(A->SetValue(5, 2, 200), std::out_of_range);

  A.reset();
  B.reset();
  builder.reset();
}

TEST(AccessorTests, get_value_test) {
  // ARRANGE
  std::vector<double> vec1{1, 51, 4, 5};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(2, 2);
  builder->FillMatrix(vec1, A);

  // ACT
  double val1 = A->GetValue(0, 0);

  // ASSERT
  EXPECT_EQ(val1, 1);
  // impossible number of rows
  EXPECT_THROW(A->GetValue(-1, 1), std::out_of_range);
  EXPECT_THROW(A->GetValue(2, 1), std::out_of_range);
  EXPECT_THROW(A->GetValue(1, -2), std::out_of_range);
  EXPECT_THROW(A->GetValue(1, 2), std::out_of_range);

  A.reset();
  builder.reset();
}

TEST(OperatorsTests, operator_assign_test) {
  // ARRANGE
  std::vector<double> vec1{1, 51, 4, 5};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  S21Matrix A = S21Matrix(2, 2);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(2, 2);
  builder->FillMatrix(vec1, B);

  A = *B;

  // ASSERT
  EXPECT_EQ(A.EqMatrix(*B.get()), 1);

  B.reset();
  builder.reset();
}

TEST(OperatorsTests, operator_eq_test) {
  // ARRANGE
  std::vector<double> vec1{1, 51, 4, 5};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(2, 2);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(2, 2);
  builder->FillMatrix(vec1, B);

  *A == *B;

  // ASSERT
  EXPECT_EQ(*A == *B.get(), 1);
  A->SetValue(0, 0, 10);
  EXPECT_EQ(*A == *B.get(), 0);

  A.reset();
  B.reset();
  builder.reset();
}

TEST(OperatorsTests, operator_sum_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4};
  std::vector<double> res{2, 4, 6, 8};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(2, 2);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(2, 2);
  builder->FillMatrix(res, B);

  S21Matrix C = *A + *A;

  // ASSERT
  EXPECT_EQ(C == *B, 1);
  A.reset();
  B.reset();
  builder.reset();
}

TEST(OperatorsTests, operator_sum_assign_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4};
  std::vector<double> res{2, 4, 6, 8};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(2, 2);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(2, 2);
  builder->FillMatrix(res, B);

  *A += *A;

  // ASSERT
  EXPECT_EQ(*A == *B, 1);
  A.reset();
  B.reset();
  builder.reset();
}

TEST(OperatorsTests, operator_sub_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(2, 2);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(2, 2);

  S21Matrix C = *A - *A;

  // ASSERT
  EXPECT_EQ(C == *B, 1);

  A.reset();
  B.reset();
  builder.reset();
}

TEST(OperatorsTests, operator_sub_assign_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(2, 2);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(2, 2);

  *A -= *A;

  // ASSERT
  EXPECT_EQ(*A == *B, 1);
  A.reset();
  B.reset();
  builder.reset();
}

TEST(OperatorsTests, operator_mul_matrix_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4, 5, 6};
  std::vector<double> vec2{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<double> res{11, 14, 17, 20, 23, 30, 37, 44, 35, 46, 57, 68};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 2);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(2, 4);
  builder->FillMatrix(vec2, B);

  std::unique_ptr<S21Matrix> C = builder->CreateMatrix(3, 4);
  builder->FillMatrix(res, C);

  // ACT
  *A **B;

  // ASSERT
  EXPECT_EQ(*A == *C, 1);
  A.reset();
  B.reset();
  C.reset();
  builder.reset();
}

TEST(OperatorsTests, operator_mul_num_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4, 5, 6};
  std::vector<double> res{3, 6, 9, 12, 15, 18};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 2);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(3, 2);
  builder->FillMatrix(res, B);

  // ACT
  *A * 3;

  // ASSERT
  EXPECT_EQ(*A == *B, 1);
  A.reset();
  B.reset();
  builder.reset();
}

TEST(OperatorsTests, operator_mul_matrix_assign_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4, 5, 6};
  std::vector<double> vec2{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<double> res{11, 14, 17, 20, 23, 30, 37, 44, 35, 46, 57, 68};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 2);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(2, 4);
  builder->FillMatrix(vec2, B);

  std::unique_ptr<S21Matrix> C = builder->CreateMatrix(3, 4);
  builder->FillMatrix(res, C);

  // ACT
  *A *= *B;

  // ASSERT
  EXPECT_EQ(*A == *C, 1);
  A.reset();
  B.reset();
  C.reset();
  builder.reset();
}

TEST(OperatorsTests, operator_mul_num_assign_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4, 5, 6};
  std::vector<double> res{3, 6, 9, 12, 15, 18};

  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 2);
  builder->FillMatrix(vec1, A);

  std::unique_ptr<S21Matrix> B = builder->CreateMatrix(3, 2);
  builder->FillMatrix(res, B);

  // ACT
  *A *= 3;

  // ASSERT
  EXPECT_EQ(*A == *B, 1);
  A.reset();
  B.reset();
  builder.reset();
}

TEST(OperatorsTests, operator_insex_test) {
  // ARRANGE
  std::vector<double> vec1{1, 2, 3, 4, 5, 6};
  std::unique_ptr<VectorsMatrixBuilder> builder{
      std::make_unique<VectorsMatrixBuilder>(VectorsMatrixBuilder())};

  std::unique_ptr<S21Matrix> A = builder->CreateMatrix(3, 2);
  builder->FillMatrix(vec1, A);

  // ACT
  double val1 = (*A)(1, 1);

  // ASSERT
  EXPECT_EQ(val1, 4);

  A.reset();
  builder.reset();
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}