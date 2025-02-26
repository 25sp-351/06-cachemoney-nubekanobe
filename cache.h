#ifndef CACHE_H
#define CACHE_H

#include <stdio.h> 

#define MAX_LARGE_MEMO_ENTRIES 1501
#define MAX_SMALL_MEMO_ENTRIES 100
#define BUFFER_SIZE 150

typedef long long KeyType; 
typedef char* ValueType;

typedef ValueType (*to_string_fnc)(KeyType);
extern to_string_fnc assigned_large_provider;
extern to_string_fnc assigned_small_provider; 
to_string_fnc original_large_provider; 
to_string_fnc original_small_provider; 

typedef ValueType (*ProviderFunction)(KeyType);

// Function prototypes
void initialize(void);
ProviderFunction set_provider(ProviderFunction downstream);  
char* large_cache_provider(KeyType key); 
char* small_cache_provider(KeyType key); 
void store_in_cache(KeyType key, ValueType value, ValueType* cache); 
char* get_from_cache(KeyType key, ValueType* cache); 
void print_cache(); 
void free_cache(); 

#endif