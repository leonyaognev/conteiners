# Compiler and flags
CXX       = gcc
CXXFLAGS  = -x c++ -std=c++20 -lstdc++ -lpthread -Wall -Wextra -Werror -I.

# Sources and objects
SRC       = logger.cpp
OBJ       = $(patsubst %.cpp, build/%.o, $(SRC))

# Final static library
TARGET    = liblogger.a

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

TOTAL := $(words $(OBJ))
DONE  := 0

# ---------------------------------------------------------------------------
all: $(TARGET)

example: $(TARGET)
	@$(CXX) $(CXXFLAGS) ./example.cpp -L. -l:./$(TARGET) -o example -DDEBUG_LEVEL=4

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	$(eval DONE := $(shell expr $(DONE) + 1))
	@$(call print_bar,$(DONE),$(TOTAL),object compilation: )

$(TARGET): $(OBJ)
	@$(call print_bar,1,2,library archive:    )
	@ar rcs $(TARGET) $(OBJ)
	@sleep 0.2
	@$(call print_bar,1,1,library archive:    )

clean:
	@rm -rf ./build ./$(TARGET) ./example

rebuild: clean all

.PHONY: all clean rebuild $(TARGET)
