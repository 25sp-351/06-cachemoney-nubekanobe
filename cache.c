#include <stdio.h> 
#include "value_to_string_conversions.h" 
#include "cache.h"

char dollar_memo[MAX_DOLLAR_MEMO_ENTRIES][BUFFER_SIZE];
char cent_memo[MAX_CENT_MEMO_ENTRIES][BUFFER_SIZE];


char* get_from_cache(long long key, char cache[][BUFFER_SIZE]) {
   
    if (key < 0 || key >= MAX_DOLLAR_MEMO_ENTRIES)
        return NULL; 

    if (cache[key][0] != '\0') {
        return cache[key];
    }

    return NULL;  // Not found in cache
}

void store_in_cache(long long key, char* value, char cache[][BUFFER_SIZE]) {

    if (key < 0 || key >= MAX_DOLLAR_MEMO_ENTRIES)
        return;  

    snprintf(cache[key], BUFFER_SIZE, "%s", value);
}

char* cached_dollars(long long int total_dollars) {
    char* result = get_from_cache(total_dollars, dollar_memo);

    if (!result) {
        result = (*original_dollar_provider)(total_dollars);
        if(total_dollars <= MAX_DOLLAR_MEMO_ENTRIES)
            store_in_cache(total_dollars, result, dollar_memo);  
    }
    return result;
}

char* cached_cents(long long int total_cents) {
    char* result = get_from_cache(total_cents, cent_memo); 
    
    if (!result) {
        result = (*original_cent_provider)(total_cents);  // Call the original function if not cached
        store_in_cache(total_cents, result, cent_memo);  // Store in cent cache
    }
    return result;
}

void initialize_cache() {
    // Initialize the dollar cache to empty strings
    for (int ix = 0; ix < MAX_DOLLAR_MEMO_ENTRIES; ix++) {
        dollar_memo[ix][0] = '\0';
    }

    // Initialize the cent cache to empty strings
    for (int ix = 0; ix < MAX_CENT_MEMO_ENTRIES; ix++) {
        cent_memo[ix][0] = '\0';
    }

}

void print_cache(){

    printf("CACHE CONTENT\n");

    for (int ix = 0; ix < MAX_DOLLAR_MEMO_ENTRIES; ix++) {
        if(dollar_memo[ix][0] != '\0')
            printf("Dollar %d: [%s]\n", ix, dollar_memo[ix]);
    }

    
    for (int ix = 0; ix < MAX_CENT_MEMO_ENTRIES; ix++) {
        if(cent_memo[ix][0] != '\0')
            printf("Cent %d: [%s]\n", ix, cent_memo[ix]);
    }

}

