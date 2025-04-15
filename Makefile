# Compiler
CC = nvc

# Compiler flags
CFLAGS = -acc -Minfo=acc 

# Target executable
TARGET = prog

# Source files
SRC = add_gpu.c

# Default rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean rule
clean:
	rm -f $(TARGET) *.o
