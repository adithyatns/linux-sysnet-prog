CC = gcc
# Include the root 'include' folder for headers
CFLAGS = -Wall -Wextra -g -I../include

# 1. Find all .c files in any subdirectory (e.g., ch04/demo.c)
SRCS := $(wildcard */*.c)

# 2. Create the target binary list (flattened to bin/demo)
# $(notdir ...) removes the folder part (ch04/demo.c -> demo.c)
BINS := $(patsubst %.c,bin/%,$(notdir $(SRCS)))

# 3. VPATH Magic: Tell Make to look inside ALL subdirectories for source files
# This fixes the "No rule to make target" error.
VPATH := $(dir $(SRCS))

# Default target
all: $(BINS)

# 4. The Build Rule
# We map bin/% (target) from %.c (source). 
# Because of VPATH, Make automatically finds where that %.c lives.
bin/%: %.c
	@mkdir -p bin
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $< -o $@

clean:
	 rm -rf bin


