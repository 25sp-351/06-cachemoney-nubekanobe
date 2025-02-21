#ifndef VALUE_TO_STRING_CONVERSIONS_H
#define VALUE_TO_STRING_CONVERSIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "constants.h"

char* cents_to_string(long long int total_cents);   
char* dollars_to_string(long long int total_dollars);  
void prepend_string(char* destination, char* source);

#endif