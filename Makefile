MAKEFLAGS += --no-print-directory

# Compiler and flags
DEBUG_LEVEL ?= 2

CC = gcc -DDEBUG_LEVEL=$(DEBUG_LEVEL)

SRC_HELP   := $(wildcard ./src/helpers/*.cpp)
HEADER_FILES = -I./ -I./src/include/ -I./src/vendor/logger/
CFLAGS     = -Wall -Wextra -Werror $(HEADER_FILES) -x c++ -std=c++20 -lstdc++
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov -O0 -g

# Sources and objects
SRC_CORE   := $(wildcard ./src/core_files/*.cpp)
SRC        := $(SRC_CORE) $(SRC_HELP)

OBJ        := $(patsubst ./src/%.cpp, build/obj/%.o, $(SRC))
OBJ_GCOV   := $(patsubst ./src/%.cpp, build/gcov/%.o, $(SRC))

# Progress counters
TOTAL      := $(words $(OBJ))
DONE       := 0

TOTAL_GCOV := $(words $(OBJ_GCOV))
DONE_GCOV  := 0

# Main targets
TARGET     = s21_matrix_oop.a
TEST_SRC   = $(wildcard ./test/*.cpp ./test/tests/manual/*.cpp ./test/tests/generate/*.cpp)
OS         := $(shell uname -s)

# ---------------------------------------------------------------------------
# Dynamic bar width (80% of terminal width minus padding)
TERM_WIDTH := $(shell stty size 2>/dev/null | awk '{print $$2}')
TERM_WIDTH := $(if $(TERM_WIDTH),$(TERM_WIDTH),80)
BAR_WIDTH  := $(shell expr $(TERM_WIDTH) \* 80 / 100 - 20)

# Function to print progress bar
define print_bar
FILLED=$$(( ($1 * $(BAR_WIDTH)) / $2 )); \
UNFILLED=$$(( $(BAR_WIDTH) - FILLED )); \
BAR=$$(printf "%0.s▓" $$(seq 1 $$FILLED)); \
SP=""; \
if [ $$UNFILLED -gt 0 ]; then \
  SP=$$(printf "%0.s░" $$(seq 1 $$UNFILLED)); \
fi; \
PCT=$$(( 100 * $1 / $2 )); \
printf "\r$3 [$$BAR$$SP] %3d%%" $$PCT; \
if [ $1 -eq $2 ]; then printf "\n"; fi
endef

# ---------------------------------------------------------------------------
all: compile_logger $(TARGET) test example gcov_report valgrind_test create_documentation

# ---------------------------------------------------------------------------
example: compile_logger mkbuild $(TARGET)
	@$(call print_bar,1,2,example compilation:)
	@$(CC) $(CFLAGS) -g -o build/example ./example/main.cpp -L. -l:$(TARGET) -lm -L./src/vendor/logger/ -l:liblogger.a
	@$(call print_bar,1,1,example compilation:)

# ---------------------------------------------------------------------------
# Library without coverage
build/obj/%.o: ./src/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(eval DONE := $(shell expr $(DONE) + 1))
	@$(call print_bar,$(DONE),$(TOTAL),target compilation: )

$(TARGET): compile_logger mkbuild $(OBJ)
	@$(call print_bar,1,2,target archive:     )
	@ar rcs $(TARGET) $(OBJ)
	@sleep 0.2
	@$(call print_bar,1,1,target archive:     )

# ---------------------------------------------------------------------------
# Library with gcov
build/gcov/%.o:  ./src/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@
	$(eval DONE_GCOV := $(shell expr $(DONE_GCOV) + 1))
	@$(call print_bar,$(DONE_GCOV),$(TOTAL_GCOV),test compilation:   )

lib_gcov: compile_logger mkbuild $(OBJ_GCOV)
	@$(call print_bar,1,2,gcov archive:       )
	@ar rcs ./build/gcov/lib_gcov.a $(OBJ_GCOV)
	@sleep 0.2
	@$(call print_bar,1,1,gcov archive:       )

# ---------------------------------------------------------------------------
test: compile_logger mkbuild lib_gcov $(OBJ_GCOV)
	@$(call print_bar,1,2,test build:         )
	@$(CC) -o build/gcov/test $(TEST_SRC) $(CFLAGS) $(GCOV_FLAGS) \
		-L./build/gcov -l:lib_gcov.a \
		-L./src/vendor/logger/ -l:liblogger.a \
		-lgtest -lm -lpthread
	@sleep 0.2
	@$(call print_bar,1,1,test build:         )

run_test: test
	@echo
	@echo "Run tests..."
	@./build/gcov/test > /tmp/s21_matrix_test.log 2>&1 || true
	@if grep -q "\[  FAILED  \]" /tmp/s21_matrix_test.log; then \
		echo "FAIL! 💥"; \
		cat /tmp/s21_matrix_test.log; \
	else \
		echo "SUCCESFUL! ✅"; \
	fi
	@rm -f /tmp/s21_matrix_test.log
	@echo

# ---------------------------------------------------------------------------
mkbuild:
	@mkdir -p ./build/coverage_html ./build/obj ./build/gcov

gcov_report: run_test
	@echo "Generating coverage report..."
	@lcov --capture --directory ./build/gcov/ \
		--ignore-errors inconsistent \
		--rc geninfo_unexecuted_blocks=1 \
		--output-file ./build/coverage_html/base.info > /dev/null 2>&1
	@lcov --remove ./build/coverage_html/base.info \
		"/usr/include/*" \
		--output-file ./build/coverage_html/base.info > /dev/null 2>&1
	@genhtml ./build/coverage_html/base.info --output-directory ./build/coverage_html/ > /dev/null 2>&1
	@echo "Coverage report: build/coverage_html/index.html ✅"
	@echo

valgrind_test: test
	@if [ "$(OS)" = "Linux" ]; then \
		echo "Run tests via valgrind..."; \
		CK_FORK=no valgrind --error-exitcode=1 --tool=memcheck --leak-check=yes ./build/gcov/test > /tmp/valgrind.log 2>&1 || true; \
	else \
		echo "Run tests via leaks..."; \
		leaks -atExit -- ./build/test > /tmp/valgrind.log 2>&1 || true; \
	fi
	@if grep -q "ERROR SUMMARY: 0 errors" /tmp/valgrind.log; then \
		echo "SUCCESFUL! ✅"; \
	else \
		echo "FAIL! 💥"; \
		cat /tmp/valgrind.log; \
	fi
	@rm -f /tmp/valgrind.log
	@echo

# ---------------------------------------------------------------------------
compile_logger: init_submodules
	@$(MAKE) -C ./src/vendor/logger

init_submodules:
	@git submodule update --init --recursive > /dev/null 2>&1

compile_commands.json:
	@bear -- make all

create_documentation:
	@doxygen > /dev/null 2>&1 || true

clean:
	@rm -rf ./build ./$(TARGET)
	@rm -rf ./app.log
	@$(MAKE) clean -C ./src/vendor/logger

rebuild: clean all

.PHONY: all example $(TARGET) test run_test mkbuild gcov_report \
        valgrind_test create_documentation clean rebuild
