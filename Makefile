# Variables for compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o seats.o fileio.o
EXEC = ars

# Default target
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Compiling individual source files
main.o: main.c seats.h fileio.h
	$(CC) $(CFLAGS) -c main.c

seats.o: seats.c seats.h
	$(CC) $(CFLAGS) -c seats.c

fileio.o: fileio.c fileio.h seats.h
	$(CC) $(CFLAGS) -c fileio.c

# Clean to remove object files and executable
clean:
	rm -f *.o $(EXEC)
