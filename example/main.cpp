#include "except.h"
#include "logger.h"
#include "s21_matrix_oop.h"

#define ROWS 10
#define COLS 10

int main(void) {
  S21Matrix m(1, 1);
  m(0, 0) = 69.420;
  double expected = 1.0 / m(0, 0);
  double result;
  (void)expected;
  (void)result;
  try {
    result = m.InverseMatrix()(0, 0);
  } catch (MatrixError& e) {
    log_info("main error: %s", e.what());
  }

  log_info("expexted: %lf  result: %lf", expected, result);

  return 0;
}
