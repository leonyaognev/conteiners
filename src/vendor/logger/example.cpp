#include "logger.h"

int main() {
  log_trace("Hello from trace");
  log_info("This is an info message");
  log_warn("Something might be wrong");
  log_error("Oops, something broke");
  return 0;
}
