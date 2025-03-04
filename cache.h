#ifndef CACHE_H
#define CACHE_H

#define MAX_LARGE_MEMO_ENTRIES 1501
#define MAX_SMALL_MEMO_ENTRIES 100
#define BUFFER_SIZE 150

typedef long long KeyType; 
typedef char* ValueType;

typedef ValueType (*to_string_fnc)(KeyType);

typedef struct {
    to_string_fnc large_values_provider;
    to_string_fnc small_values_provider;
} provider_set;


// Function prototype for dynamically loading cache module
typedef void (*set_provider_fnc)(provider_set *provider);
set_provider_fnc load_cache_module(const char *module_path);

#endif