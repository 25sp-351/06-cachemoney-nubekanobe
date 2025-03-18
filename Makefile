# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -g

# Target executable
TARGET = money_main

# Object files 
OBJS = number_to_words_main.o value_to_string_conversions.o

# Shared Library for dynamic loading
LIBRARY = libcache.so

# Default target
all: $(TARGET) $(LIBRARY)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -ldl

# Compile source files to object files
number_to_words_main.o: number_to_words_main.c value_to_string_conversions.h cache.h
	$(CC) $(CFLAGS) -c number_to_words_main.c -o number_to_words_main.o

value_to_string_conversions.o: value_to_string_conversions.c value_to_string_conversions.h constants.h
	$(CC) $(CFLAGS) -c value_to_string_conversions.c -o value_to_string_conversions.o

# Create the shared library (cache.o)
$(LIBRARY): cache.o
	$(CC) -shared -o $(LIBRARY) cache.o 

# Compile cache as a shared object (fPIC)
cache.o: cache.c cache.h
	$(CC) $(CFLAGS) -fPIC -c cache.c -o cache.o

# Run tests
test: $(TARGET)
	./tests.sh

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET) $(LIBRARY) cache.o
