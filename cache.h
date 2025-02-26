#ifndef CACHE_H
#define CACHE_H

#define MAX_LARGE_MEMO_ENTRIES 1501
#define MAX_SMALL_MEMO_ENTRIES 100
#define BUFFER_SIZE 150

typedef long long KeyType; 
typedef char* ValueType;

typedef ValueType (*to_string_fnc)(KeyType);
// Function pointers available to main
extern to_string_fnc assigned_large_provider;
extern to_string_fnc assigned_small_provider; 

// Function prototypes available to main
void initialize_cache(to_string_fnc* assigned_large_provider, to_string_fnc* assigned_small_provider); 
void print_cache(); // fordebugging
void free_cache(); 

#endif