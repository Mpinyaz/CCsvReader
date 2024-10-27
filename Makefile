# Define the compiler and compiler flags
CC = gcc
CFLAGS = -Wall -g3 -Wextra
DBG = lldb
# Define the source and build directories
SRC_DIR = src
BUILD_DIR = build

# Define the source file and output binary
SRC = $(SRC_DIR)/main.c
OUT = $(BUILD_DIR)/csvrdr

# Rule to build the program
all: $(OUT)

build-dir:
	if [ ! -d build]; then mkdir build; fi
build-main:
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)
build-test:
	$(CC) $(CFLAGS) -o build/test src/test.c
debug:
	$(DBG) ./build/main
# Rule to compile the source file
$(OUT): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# Rule to clean the build directory
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean
