#ifndef VALUE_TO_STRING_CONVERSIONS_H
#define VALUE_TO_STRING_CONVERSIONS_H

char* cents_to_string(long long int total_cents);   
char* dollars_to_string(long long int total_dollars);  
void prepend_string(char* destination, char* source);

extern const char* ones_and_teens[];
extern const char* tens[];
extern const char* thousand_multiplier[]; 

#endif