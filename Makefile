# Makefile

# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -g

# Target executable
TARGET = ntw

# Object files
OBJS = number_to_words_main.o value_to_string_conversions.o cache.o

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile source files to object files
number_to_words_main.o: number_to_words_main.c value_to_string_conversions.h cache.h constants.h
	$(CC) $(CFLAGS) -c number_to_words_main.c -o number_to_words_main.o

value_to_string_conversions.o: value_to_string_conversions.c value_to_string_conversions.h constants.h cache.h
	$(CC) $(CFLAGS) -c value_to_string_conversions.c -o value_to_string_conversions.o

cache.o: cache.c cache.h 
	$(CC) $(CFLAGS) -c cache.c -o cache.o

# Run tests
test: $(TARGET)
	./tests.sh

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

