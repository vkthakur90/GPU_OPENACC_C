# Makefile for compiling the code with NVIDIA HPC SDK (nvc)
# targeting GPUs with compute capability 70 (cc70) using OpenACC.
#
# Usage Examples:
#   make                  # Uses the default MAX_DATA and BATCH_DATA values.
#   make MAX_DATA=2000000 BATCH_DATA=50000   # Overrides the default values.

# Set the compiler to nvc from the NVIDIA HPC SDK.
CC      := nvc

# Compiler flags:
# -O2           : Standard optimization level.
# -acc          : Enable OpenACC support.
# -gpu=cc70     : Target NVIDIA GPUs with compute capability 70.
# -Minfo=accel  : Display accelerator-related optimization information.
CFLAGS  := -O2 -acc -gpu=cc70 -Minfo=accel

# Default values for the macros. They can be overridden from the command line.
MAX_DATA   ?= 1000000
BATCH_DATA ?= 100000

# Append macro definitions to the compiler flags.
CFLAGS += -DMAX_DATA=$(MAX_DATA) -DBATCH_DATA=$(BATCH_DATA)

# Source file name and the target executable.
SRC    := main.c
TARGET := main

# Phony targets.
.PHONY: all clean

# Default target: build the main executable.
all: $(TARGET)

# Build rule for the target.
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean target to remove the compiled executable.
clean:
	rm -f $(TARGET)
