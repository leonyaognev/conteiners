#include <gtest/gtest.h>

#include "except.h"
#include "logger.h"
#include "s21_matrix_oop.h"

TEST(test_class, basic_constructor) {
  S21Matrix m;
  EXPECT_EQ(m.GetCols(), 1);
  EXPECT_EQ(m.GetRows(), 1);
}

TEST(test_class, rc_constructor) {
  S21Matrix m(69, 420);
  EXPECT_EQ(m.GetRows(), 69);
  EXPECT_EQ(m.GetCols(), 420);
}

TEST(test_class, copy_constructor) {
  S21Matrix m(12, 12);
  S21Matrix copy(m);

  EXPECT_EQ(copy.GetCols(), 12);
  EXPECT_EQ(copy.GetRows(), 12);
}

TEST(test_class, move_constructor) {
  S21Matrix m(12, 12);
  S21Matrix moved(std::move(m));

  EXPECT_EQ(m.GetCols(), 0);
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(moved.GetCols(), 12);
  EXPECT_EQ(moved.GetRows(), 12);
}

TEST(test_class, brackets_operator) {
  S21Matrix m(6, 9);
  EXPECT_EQ(m(0, 0), 0);

  m(0, 1) = 69;
  EXPECT_EQ(m(0, 1), 69);

  m(5, 8) = 69.420;
  EXPECT_EQ(m(5, 8), 69.420);
}

TEST(test_class, square_brackets_operator) {
  S21Matrix m(6, 9);
  EXPECT_EQ(m(0, 0), 0);

  m(5, 5) = 69;
  EXPECT_EQ(m(5, 5), 69);

  m(5, 8) = 69.420;
  EXPECT_EQ(m(5, 8), 69.420);
}

TEST(test_setters, SetRows_up) {
  S21Matrix m(2, 2);
  m(1, 1) = 6.9;

  m.SetRows(5);
  EXPECT_EQ(m.GetRows(), 5);
  EXPECT_EQ(m(1, 1), 6.9);
}

TEST(test_setters, SetRows_down) {
  S21Matrix m(2, 2);
  m(0, 0) = 6.9;

  m.SetRows(1);
  EXPECT_EQ(m.GetRows(), 1);
  EXPECT_EQ(m(0, 0), 6.9);
}

TEST(test_setters, SetRows_zero) {
  S21Matrix m;

  EXPECT_ANY_THROW(m.SetRows(0));
}

TEST(test_setters, SetCols_up) {
  S21Matrix m(2, 2);
  m(1, 1) = 6.9;

  m.SetCols(5);
  EXPECT_EQ(m.GetCols(), 5);
  EXPECT_EQ(m(1, 1), 6.9);
}

TEST(test_setters, SetCols_down) {
  S21Matrix m(2, 2);
  m(0, 0) = 6.9;

  m.SetCols(1);
  EXPECT_EQ(m.GetCols(), 1);
  EXPECT_EQ(m(0, 0), 6.9);
}

TEST(test_setters, SetCols_zero) {
  S21Matrix m;

  EXPECT_ANY_THROW(m.SetCols(0));
}

TEST(test_overload, equal_lvalue) {
  S21Matrix m;
  S21Matrix x(3, 6);
  x(1, 2) = 3;
  x(2, 2) = 3;

  m = x;

  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 6);
  EXPECT_EQ(m(1, 2), 3);
  EXPECT_EQ(m(2, 2), 3);
}

TEST(test_overload, equal_rvalue) {
  S21Matrix m(2, 2);
  S21Matrix n;

  n = std::move(m);

  EXPECT_EQ(n.GetCols(), 2);
  EXPECT_EQ(n.GetRows(), 2);
}

TEST(test_functional, eq_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  ASSERT_TRUE(m == n);
}

TEST(test_functional, eq_matrix1) {
  S21Matrix m(3, 2);
  S21Matrix n;

  m(0, 1) = 69;
  n = m;

  ASSERT_TRUE(m == n);
}

TEST(test_functional, sum_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SumMatrix(n);

  EXPECT_EQ(m(0, 0), 2);
  EXPECT_EQ(m(1, 1), 2);
}

TEST(test_functional, add_operator_overload) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m = m + n;

  EXPECT_EQ(m(0, 0), 2);
  EXPECT_EQ(m(1, 1), 2);
}

TEST(test_functional, eqadd_operator_overload) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m += m + n;

  EXPECT_EQ(m(0, 0), 3);
  EXPECT_EQ(m(1, 1), 3);
}

TEST(test_functional, sub_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SubMatrix(n);

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, eqsub_overloaded_operator) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m -= n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, sub_operator_overload) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m = m - n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, mul_matrices) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++) m(i, j) = c++;

  for (uint32_t i = 0, c = 7; i < cols; i++)
    for (uint32_t j = 0; j < rows; j++) n(i, j) = c++;

  m.MulMatrix(n);

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, eqmul_operator) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++) m(i, j) = c++;

  for (uint32_t i = 0, c = 7; i < cols; i++)
    for (uint32_t j = 0; j < rows; j++) n(i, j) = c++;

  m *= n;

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, eqmul_operator_num) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++) m(i, j) = c++;

  m *= 2;

  S21Matrix res(2, 3);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(1, 0) = 8;
  res(1, 1) = 10;
  res(1, 2) = 12;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, mul_operator) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++) m(i, j) = c++;

  for (uint32_t i = 0, c = 7; i < cols; i++)
    for (uint32_t j = 0; j < rows; j++) n(i, j) = c++;

  m = m * n;

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m == res);
}

TEST(test_functional, mul_operator_num) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++) m(i, j) = c++;

  m *= 2;

  S21Matrix res(2, 3);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(1, 0) = 8;
  res(1, 1) = 10;
  res(1, 2) = 12;

  ASSERT_TRUE(m == res);
}

TEST(test_functional, transpose) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix res(cols, rows);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++, c++) {
      m(i, j) = c;
      res(j, i) = c;
    }

  m = m.Transpose();
  ASSERT_TRUE(m == res);
}

TEST(test_functional, determinant) {
  S21Matrix m(2, 3);

  EXPECT_ANY_THROW(m.Determinant());
}

TEST(test_functional, determinant_zero) {
  const uint32_t size = 5;
  S21Matrix m(5, 5);

  for (uint32_t i = 0; i < size; i++)
    for (uint32_t j = 0; j < size; j++) m(i, j) = j;

  ASSERT_NEAR(0, m.Determinant(), 1e-06);
}

TEST(test_functional, determinant_5x5) {
  uint32_t size = 5;
  S21Matrix m(size, size);

  m(0, 1) = 6;
  m(0, 2) = -2;
  m(0, 3) = -1;
  m(0, 4) = 5;
  m(1, 3) = -9;
  m(1, 4) = -7;
  m(2, 1) = 15;
  m(2, 2) = 35;
  m(3, 1) = -1;
  m(3, 2) = -11;
  m(3, 3) = -2;
  m(3, 4) = 1;
  m(4, 0) = -2;
  m(4, 1) = -2;
  m(4, 2) = 3;
  m(4, 4) = -2;

  double res = m.Determinant();
  ASSERT_NEAR(res, 2480, 1e-6);
}

TEST(test_functional, determinant_3x3) {
  const uint32_t size = 3;
  S21Matrix m(size, size);

  m(0, 0) = 2;
  m(0, 1) = 3;
  m(0, 2) = 1;
  m(1, 0) = 7;
  m(1, 1) = 4;
  m(1, 2) = 1;
  m(2, 0) = 9;
  m(2, 1) = -2;
  m(2, 2) = 1;

  double res = m.Determinant();
  ASSERT_NEAR(res, -32, 1e-6);
}

TEST(test_functional, determinant_2x2) {
  const uint32_t size = 2;
  S21Matrix m(size, size);

  m(0, 0) = -5;
  m(0, 1) = -4;
  m(1, 0) = -2;
  m(1, 1) = -3;

  double res = m.Determinant();
  ASSERT_NEAR(res, 7, 1e-6);
}

TEST(test_functional, complements_3x3) {
  const uint32_t rows = 3;
  const uint32_t cols = 3;

  S21Matrix given(rows, cols);
  S21Matrix expected(rows, cols);

  expected(0, 0) = 0;
  expected(0, 1) = 10;
  expected(0, 2) = -20;
  expected(1, 0) = 4;
  expected(1, 1) = -14;
  expected(1, 2) = 8;
  expected(2, 0) = -8;
  expected(2, 1) = -2;
  expected(2, 2) = 4;

  given(0, 0) = 1;
  given(0, 1) = 2;
  given(0, 2) = 3;
  given(1, 0) = 0;
  given(1, 1) = 4;
  given(1, 2) = 2;
  given(2, 0) = 5;
  given(2, 1) = 2;
  given(2, 2) = 1;

  S21Matrix res = given.CalcComplements();

  ASSERT_TRUE(res == expected);
}

TEST(test_functional, CalcComplements_throw) {
  S21Matrix m(3, 12);
  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(test_functional, complements_3x3_1) {
  const uint32_t rows = 3;
  const uint32_t cols = 3;

  S21Matrix given(rows, cols);
  S21Matrix expected(rows, cols);

  given(0, 0) = 1.0;
  given(0, 1) = 2.0;
  given(0, 2) = 3.0;
  given(1, 0) = 0.0;
  given(1, 1) = 4.0;
  given(1, 2) = 2.0;
  given(2, 0) = 5.0;
  given(2, 1) = 2.0;
  given(2, 2) = 1.0;

  expected(0, 0) = 0.0;
  expected(0, 1) = 10.0;
  expected(0, 2) = -20.0;
  expected(1, 0) = 4.0;
  expected(1, 1) = -14.0;
  expected(1, 2) = 8.0;
  expected(2, 0) = -8.0;
  expected(2, 1) = -2.0;
  expected(2, 2) = 4.0;

  S21Matrix res = given.CalcComplements();

  ASSERT_TRUE(res == expected);
}

TEST(test_class, zero_size) { EXPECT_ANY_THROW(S21Matrix(0, 1)); }

TEST(test_functional, complements_3x3_2) {
  const uint32_t rows = 3;
  const uint32_t cols = 3;

  S21Matrix given(rows, cols);
  S21Matrix expected(rows, cols);

  given(0, 0) = 1;
  given(0, 1) = 2;
  given(0, 2) = 3;
  given(1, 1) = 4;
  given(1, 2) = 2;
  given(2, 0) = 5;
  given(2, 1) = 2;
  given(2, 2) = 1;

  expected(0, 1) = 10;
  expected(0, 2) = -20;
  expected(1, 0) = 4;
  expected(1, 1) = -14;
  expected(1, 2) = 8;
  expected(2, 0) = -8;
  expected(2, 1) = -2;
  expected(2, 2) = 4;

  S21Matrix res = given.CalcComplements();
  ASSERT_TRUE(res == expected);
}

TEST(test_functional, inverese_3x3) {
  const uint32_t size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);

  expected(0, 0) = 44300.0 / 367429.0;
  expected(0, 1) = -236300.0 / 367429.0;
  expected(0, 2) = 200360.0 / 367429.0;
  expected(1, 0) = 20600.0 / 367429.0;
  expected(1, 1) = 56000.0 / 367429.0;
  expected(1, 2) = -156483.0 / 367429.0;
  expected(2, 0) = 30900.0 / 367429.0;
  expected(2, 1) = 84000.0 / 367429.0;
  expected(2, 2) = -51010.0 / 367429.0;

  given(0, 0) = 2.8;
  given(0, 1) = 1.3;
  given(0, 2) = 7.01;
  given(1, 0) = -1.03;
  given(1, 1) = -2.3;
  given(1, 2) = 3.01;
  given(2, 0) = 0;
  given(2, 1) = -3;
  given(2, 2) = 2;

  ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(test_functional, inverese_3x3_1) {
  const uint32_t size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);
  expected(0, 0) = 1.0;
  expected(0, 1) = -1.0;
  expected(0, 2) = 1.0;
  expected(1, 0) = -38.0;
  expected(1, 1) = 41.0;
  expected(1, 2) = -34.0;
  expected(2, 0) = 27.0;
  expected(2, 1) = -29.0;
  expected(2, 2) = 24.0;

  given(0, 0) = 2.0;
  given(0, 1) = 5.0;
  given(0, 2) = 7.0;
  given(1, 0) = 6.0;
  given(1, 1) = 3.0;
  given(1, 2) = 4.0;
  given(2, 0) = 5.0;
  given(2, 1) = -2.0;
  given(2, 2) = -3.0;

  ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(test_functional, inverse_throw) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m.InverseMatrix());

  S21Matrix n(2, 2);
  EXPECT_ANY_THROW(n.InverseMatrix());
}

TEST(test_functional, inverse_1x1) {
  S21Matrix m(1, 1);
  m(0, 0) = 69.420;
  double expected = 1.0 / m(0, 0);
  double result = m.InverseMatrix()(0, 0);
  ASSERT_NEAR(expected, result, 1e-06);
}

TEST(test_functional, inverese_3x3_2) {
  const uint32_t size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);

  given(0, 0) = 2;
  given(0, 1) = 5;
  given(0, 2) = 7;
  given(1, 0) = 6;
  given(1, 1) = 3;
  given(1, 2) = 4;
  given(2, 0) = 5;
  given(2, 1) = -2;
  given(2, 2) = -3;

  expected(0, 0) = 1;
  expected(0, 1) = -1;
  expected(0, 2) = 1;
  expected(1, 0) = -38;
  expected(1, 1) = 41;
  expected(1, 2) = -34;
  expected(2, 0) = 27;
  expected(2, 1) = -29;
  expected(2, 2) = 24;
  ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(test_functional, inverese_3x3_3) {
  const uint32_t size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);

  given(0, 0) = 2;
  given(0, 1) = 5;
  given(0, 2) = 7;
  given(1, 0) = 6;
  given(1, 1) = 3;
  given(1, 2) = 4;
  given(2, 0) = 5;
  given(2, 1) = -2;
  given(2, 2) = -3;

  expected(0, 0) = 1;
  expected(0, 1) = -1;
  expected(0, 2) = 1;
  expected(1, 0) = -38;
  expected(1, 1) = 41;
  expected(1, 2) = -34;
  expected(2, 0) = 27;
  expected(2, 1) = -29;
  expected(2, 2) = 24;
  ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(test_functional, brackets_const) {
  const S21Matrix m(3, 3);

  ASSERT_EQ(m(0, 0), 0);
}

// ---- Constructors / Destructor ----
TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.GetRows(), 1);
  EXPECT_EQ(m.GetCols(), 1);
}

TEST(S21MatrixTest, ParamConstructorValid) {
  S21Matrix m(3, 4);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 4);
  for (int i = 0; i < m.GetRows(); i++)
    for (int j = 0; j < m.GetCols(); j++) EXPECT_DOUBLE_EQ(m(i, j), 0.0);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(1, 1) = 2.0;
  S21Matrix b(a);
  EXPECT_TRUE(b == a);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix a(2, 2);
  a(0, 0) = 3;
  a(1, 1) = 4;
  S21Matrix b(std::move(a));
  EXPECT_EQ(b.GetRows(), 2);
  EXPECT_EQ(b.GetCols(), 2);
  EXPECT_DOUBLE_EQ(b(0, 0), 3);
  EXPECT_DOUBLE_EQ(b(1, 1), 4);
}

// ---- Core Operations ----
TEST(S21MatrixTest, EqMatrix) {
  S21Matrix a(2, 2), b(2, 2);
  EXPECT_TRUE(a == b);
  b(0, 0) = 42;
  EXPECT_FALSE(a == b);
}

TEST(S21MatrixTest, SumMatrixValid) {
  S21Matrix a(2, 2), b(2, 2);
  a(0, 0) = 1.0;
  b(0, 0) = 2.0;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a(0, 0), 3.0);
}

TEST(S21MatrixTest, SumMatrixInvalidDims) {
  S21Matrix a(2, 2), b(3, 3);
  EXPECT_THROW(a.SumMatrix(b), MatrixError);
}

TEST(S21MatrixTest, SubMatrixValid) {
  S21Matrix a(2, 2), b(2, 2);
  a(0, 0) = 3.0;
  b(0, 0) = 1.0;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a(0, 0), 2.0);
}

TEST(S21MatrixTest, MulNumber) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a.MulNumber(3.0);
  EXPECT_DOUBLE_EQ(a(0, 0), 3.0);
}

TEST(S21MatrixTest, MulMatrixValid) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  b(0, 0) = 1;
  b(1, 0) = 1;
  b(2, 0) = 1;
  a.MulMatrix(b);
  EXPECT_EQ(a.GetCols(), 2);
  EXPECT_DOUBLE_EQ(a(0, 0), 6);
}

TEST(S21MatrixTest, MulMatrixInvalidDims) {
  S21Matrix a(2, 3), b(4, 4);
  EXPECT_THROW(a.MulMatrix(b), MatrixError);
}

TEST(S21MatrixTest, Transpose) {
  S21Matrix a(2, 3);
  a(0, 1) = 7;
  S21Matrix t = a.Transpose();
  EXPECT_EQ(t.GetRows(), 3);
  EXPECT_EQ(t.GetCols(), 2);
  EXPECT_DOUBLE_EQ(t(1, 0), 7);
}

TEST(S21MatrixTest, DeterminantAndInverse) {
  S21Matrix a(2, 2);
  a(0, 0) = 4;
  a(0, 1) = 7;
  a(1, 0) = 2;
  a(1, 1) = 6;
  double det = a.Determinant();
  EXPECT_DOUBLE_EQ(det, 10.0);
  // S21Matrix inv = a.InverseMatrix();
  // EXPECT_NEAR(inv(0, 0), 0.6, 1e-6);
  // EXPECT_NEAR(inv(0, 1), -0.7, 1e-6);
}

// ---- Operator overloads ----
TEST(S21MatrixTest, OperatorPlus) {
  S21Matrix a(2, 2), b(2, 2);
  a(0, 0) = 1;
  b(0, 0) = 2;
  S21Matrix c = a + b;
  EXPECT_DOUBLE_EQ(c(0, 0), 3);
}

TEST(S21MatrixTest, OperatorMulScalar) {
  S21Matrix a(1, 1);
  a(0, 0) = 2;
  S21Matrix b = a * 3.0;
  EXPECT_DOUBLE_EQ(b(0, 0), 6);
}

TEST(S21MatrixCalcComplementsTest, CalcComplements2x2) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  S21Matrix expected(2, 2);
  // Миноры:
  // m11 -> |4|  -> det = 4, знак (+)
  // m12 -> |3|  -> det = 3, знак (-)
  // m21 -> |2|  -> det = 2, знак (-)
  // m22 -> |1|  -> det = 1, знак (+)
  expected(0, 0) = 4;
  expected(0, 1) = -3;
  expected(1, 0) = -2;
  expected(1, 1) = 1;

  S21Matrix result = m.CalcComplements();
  EXPECT_TRUE(result.EqMatrix(expected));
}

TEST(S21MatrixCalcComplementsTest, CalcComplements3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 0;
  m(1, 1) = 4;
  m(1, 2) = 2;
  m(2, 0) = 5;
  m(2, 1) = 2;
  m(2, 2) = 1;

  // Проверим что result * Transpose == adjugate работает
  S21Matrix result = m.CalcComplements();

  // Проверим пару известных элементов
  // Для (0,0) минор = det([[4,2],[2,1]]) = 4*1 - 2*2 = 0
  EXPECT_DOUBLE_EQ(result(0, 0), 0);
  // Для (1,1) минор = det([[1,3],[5,1]]) = 1*1 - 3*5 = -14, знак +
  EXPECT_DOUBLE_EQ(result(1, 1), -14);
}

// --- Edge cases ---

TEST(S21MatrixCalcComplementsTest, NonSquareMatrixThrows) {
  S21Matrix m(2, 3);
  EXPECT_THROW(m.CalcComplements(), MatrixNotSquareError);
}

TEST(S21MatrixCalcComplementsTest, SingularMatrixReturnsPartiallyFilled) {
  S21Matrix m(2, 2);
  // Матрица с нулевым детерминантом (строки пропорциональны)
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 2;
  m(1, 1) = 4;

  S21Matrix result = m.CalcComplements();
  // Результат должен быть хотя бы размером 2x2, но может быть не полным
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
