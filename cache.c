#include <stdio.h> 
#include <stdlib.h>
#include "cache.h"

// ===== Arrays to store cache values ===== //
ValueType* large_cache;
ValueType* small_cache;

// Function pointers to store original providers //
to_string_fnc original_large_provider = NULL;
to_string_fnc original_small_provider = NULL;

// ========= Function prototypes ========= //
ValueType large_cache_provider(KeyType key); 
ValueType small_cache_provider(KeyType key); 
void store_in_cache(KeyType key, ValueType value, ValueType* cache); 
ValueType get_from_cache(KeyType key, ValueType* cache); 

// ======== INITIALIZE_CACHE ============= //
// Allocate memory and initialize with     //
// empty strings. Assign function pointers // 
// to the original providers.              //
// ======================================= //

void initialize_cache(to_string_fnc* assigned_large_provider, to_string_fnc* assigned_small_provider){

    large_cache = (char**)malloc(MAX_LARGE_MEMO_ENTRIES * sizeof(char*));
    small_cache = (char**)malloc(MAX_SMALL_MEMO_ENTRIES * sizeof(char*));

    for (int ix = 0; ix < MAX_LARGE_MEMO_ENTRIES; ix++) {
        large_cache[ix] = (char*)malloc(BUFFER_SIZE * sizeof(char));
        large_cache[ix][0] = '\0'; 
    }

    for (int ix = 0; ix < MAX_SMALL_MEMO_ENTRIES; ix++) {
        small_cache[ix] = (char*)malloc(BUFFER_SIZE * sizeof(char));
        small_cache[ix][0] = '\0'; 
    }

    original_large_provider = *assigned_large_provider; 
    original_small_provider = *assigned_small_provider; 
    *assigned_large_provider = large_cache_provider;
    *assigned_small_provider = small_cache_provider; 
  

}

// ========= LARGE_CACHE_PROVIDER ====== //
// Take a key that represents a dollar   //
// amount, and checks that cache to      //
// retrieve a stored value.              //
//                                       // 
// If a result is not found, calls the   //
// original provider to generate the     //
// value.                                //
//                                       //
// If the key is within bounds, stores   //
// the value into the cache.             // 
// ===================================== // 

ValueType large_cache_provider(KeyType key) {
    ValueType result = get_from_cache(key, large_cache);

    if (result == NULL) {
        result = (*original_large_provider)(key);

        if(key >= 0 && key <= MAX_LARGE_MEMO_ENTRIES)
            store_in_cache(key, result, large_cache);  
    }
    return result;
}

// ========= SMALL_CACHE_PROVIDER ====== //
// Take a key that represents a cents    //
// amount, and checks that cache to      //
// retrieve a stored value.              //
//                                       // 
// If a result is not found, calls the   //
// original provider to generate the     //
// value.                                //
//                                       //
// If the key is within bounds, stores   //
// the value into the cache.             // 
// ===================================== // 

ValueType small_cache_provider(KeyType key) {
    ValueType result = get_from_cache(key, small_cache); 
    
    if (result == NULL) {
        result = (*original_small_provider)(key);

        store_in_cache(key, result, small_cache);  
    }
    return result;
}

// ========= GET_FROM_CACHE ============ //
// Take a key that and validates that it //
// is within bounds. Returns the value   // 
// stored at that index.                 //
// ===================================== // 

ValueType get_from_cache(KeyType key, ValueType* cache) {
   
    if (key < 0 || key >= MAX_LARGE_MEMO_ENTRIES)
        return NULL; 

    if (cache[key][0] != '\0') {
        return cache[key];
    }

    return NULL;  
}

// ========= STORE_IN_CACHE ============ //
// Take a key, a value associated with   //
// that key, and a cache to store that   //
// value.                                //
//                                       //
// Validates that the key is within      // 
// bounds, and stores the value at that  //
// key index.                            //
// ===================================== // 

void store_in_cache(KeyType key, ValueType value, ValueType* cache) {

    if (key < 0 || key >= MAX_LARGE_MEMO_ENTRIES)
        return;  

    snprintf(cache[key], BUFFER_SIZE, "%s", value);
}


// ====== PRINT_CACHE (FOR DEBUG) ===== //
// Output contents of cache if index    //
// does not contain and empty string    //
// ==================================== // 

void print_cache(){

    printf("LARGE CACHE CONTENT\n");

    for (int ix = 0; ix < MAX_LARGE_MEMO_ENTRIES; ix++) {
        if(large_cache[ix][0] != '\0')
            printf("Key %d, Value: [%s]\n", ix, large_cache[ix]);
    }

    printf("\nSMALL CACHE CONTENT\n");
    
    for (int ix = 0; ix < MAX_SMALL_MEMO_ENTRIES; ix++) {
        if(small_cache[ix][0] != '\0')
            printf("Key %d, Value: [%s]\n", ix, small_cache[ix]);
    }

}

// =========== FREE_CACHE ============ //
// Deallocate memory used for caches   //
// =================================== // 

void free_cache() {

    if(large_cache){
        for (int ix = 0; ix < MAX_LARGE_MEMO_ENTRIES; ix++) {
            free(large_cache[ix]);  
        }
        free(large_cache);  
        large_cache = NULL; 
    }

    if(small_cache){
        for (int ix = 0; ix < MAX_SMALL_MEMO_ENTRIES; ix++) {
            free(small_cache[ix]);  
        }
        free(small_cache); 
        small_cache = NULL; 
    }
}
