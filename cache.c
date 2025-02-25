#include <stdio.h> 
#include "cache.h"

char dollar_cache[MAX_DOLLAR_MEMO_ENTRIES][BUFFER_SIZE];
char cent_cache[MAX_CENT_MEMO_ENTRIES][BUFFER_SIZE];

// ========= GET_FROM_CACHE ============ //
// Take a key that represents either a   //
// dollar or cent value, and validates   //
// that it is within bounds. Returns the //
// value stored at that index.           //
// ===================================== // 

char* get_from_cache(long long key, char cache[][BUFFER_SIZE]) {
   
    if (key < 0 || key >= MAX_DOLLAR_MEMO_ENTRIES)
        return NULL; 

    if (cache[key][0] != '\0') {
        return cache[key];
    }

    return NULL;  // Not found in cache
}

// ========= STORE_IN_CACHE ============ //
// Take a key that represents either a   //
// dollar or cent value, a value         //
// associated with that key, and a cache //
// to store that value.                  //
//                                       //
// Validates that the key is within      // 
// bounds, and stores the value at that  //
// key index.                            //
// ===================================== // 


void store_in_cache(long long key, char* value, char cache[][BUFFER_SIZE]) {

    if (key < 0 || key >= MAX_DOLLAR_MEMO_ENTRIES)
        return;  

    snprintf(cache[key], BUFFER_SIZE, "%s", value);
}

// ========= CACHED_DOLLARS ============ //
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

char* cached_dollars(long long int key) {
    char* result = get_from_cache(key, dollar_cache);

    if (!result) {
        result = (*original_dollar_provider)(key);
        if(key >= 0 && key <= MAX_DOLLAR_MEMO_ENTRIES)
            store_in_cache(key, result, dollar_cache);  
    }
    return result;
}

// ========= CACHED_CENTS ============== //
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

char* cached_cents(long long int key) {
    char* result = get_from_cache(key, cent_cache); 
    
    if (!result) {
        result = (*original_cent_provider)(key);  // Call the original function if not cached
        store_in_cache(key, result, cent_cache);  // Store in cent cache
    }
    return result;
}

// ====== INITIALIZE_CACHE ============ //
// Initialize cache to empty strings    //
// ==================================== //

void initialize_cache() {

    for (int ix = 0; ix < MAX_DOLLAR_MEMO_ENTRIES; ix++) {
        dollar_cache[ix][0] = '\0';
    }

    for (int ix = 0; ix < MAX_CENT_MEMO_ENTRIES; ix++) {
        cent_cache[ix][0] = '\0';
    }

}

// ====== PRINT_CACHE (FOR DEBUG) ===== //
// Output contents of cache if index    //
// does not contain and empty string    //
// ==================================== // 

void print_cache(){

    printf("CACHE CONTENT\n");

    for (int ix = 0; ix < MAX_DOLLAR_MEMO_ENTRIES; ix++) {
        if(dollar_cache[ix][0] != '\0')
            printf("Dollar %d: [%s]\n", ix, dollar_cache[ix]);
    }

    
    for (int ix = 0; ix < MAX_CENT_MEMO_ENTRIES; ix++) {
        if(cent_cache[ix][0] != '\0')
            printf("Cent %d: [%s]\n", ix, cent_cache[ix]);
    }

}

