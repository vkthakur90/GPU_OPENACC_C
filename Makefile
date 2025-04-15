# Makefile for NVHPC GPU code with cc70 compute arch and -Minfo=accel reporting,
# with the ability to override MAX_DATA at compile time.

# Compiler
CC = nvc

# Default MAX_DATA value; override by running, e.g., `make MAX_DATA=2000000`
MAX_DATA ?= 1000000

# Compiler flags:
#   -gpu=cc70 : generates code for NVIDIA GPU architecture compute capability 7.0
#   -Minfo=accel : displays accelerator optimization information during compilation
#   -O2 : optimization flag (adjust as necessary)
#   -DMAX_DATA=value : passes the value of MAX_DATA to the preprocessor
CFLAGS = -gpu=cc70 -Minfo=accel -O2 -DMAX_DATA=$(MAX_DATA)

# Target executable name and source files
TARGET = prog
SRCS = add_gpu.c

# Rule to build the target executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean up generated files
.PHONY: clean
clean:
	rm -f $(TARGET)
