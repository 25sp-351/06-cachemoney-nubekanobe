#ifndef CACHE_H
#define CACHE_H

#include <stdio.h> 

#define MAX_DOLLAR_MEMO_ENTRIES 1501
#define MAX_CENT_MEMO_ENTRIES 100
#define BUFFER_SIZE 150

typedef char* (*string_conversion_fnc)(long long);
extern string_conversion_fnc dollar_provider;
extern string_conversion_fnc cent_provider; 
extern string_conversion_fnc original_cent_provider; 
extern string_conversion_fnc original_dollar_provider; 


// Function prototypes for memoization
void initialize_cache(); 
void print_cache(); 
char* cached_dollars(long long total_dollars); 
char* cached_cents(long long total_cents); 
void store_in_cache(long long key, char* value, char cache[][BUFFER_SIZE]); 
char* get_from_cache(long long key, char cache[][BUFFER_SIZE]); 

#endif 