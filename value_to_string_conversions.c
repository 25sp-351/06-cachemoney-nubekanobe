#include "value_to_string_conversions.h"

// ========= CENTS_TO_STRING ============= //
// This function takes in the total cents  //
// (represented by the last two digits of  //
// the input integer) and converts it to a //
// text string. Returns a pointer to that  //
// string to the caller                    //
// ======================================= //

char* cents_to_string(long long int total_cents) {

    static char cents_string[BUFFER_SIZE]; 
    cents_string[0] = '\0';
    
    static char* ones_and_teens[] = {
        "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", 
        "eighteen", "nineteen"      
    };

    static char* tens[] = {
        "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"      
    };

    if(total_cents == 1){
        snprintf(cents_string, BUFFER_SIZE, "one cent"); 
        return cents_string; 
    }

    if(total_cents == 0){
        cents_string[0] = '\0'; 
        return cents_string; 
    }

    long long int cents_tens = total_cents / DIGIT_SEPERATOR;
    long long int cents_ones = total_cents % DIGIT_SEPERATOR; 

    if(cents_tens < CHECK_IF_TEENS)
        snprintf(cents_string, BUFFER_SIZE, "%s cents", ones_and_teens[total_cents]);

    if(cents_tens >= CHECK_IF_TEENS && cents_ones == 0)
        snprintf(cents_string, BUFFER_SIZE, "%s cents", tens[cents_tens]);
    
    if(cents_tens >= CHECK_IF_TEENS && cents_ones > 0)
        snprintf(cents_string, BUFFER_SIZE, "%s-%s cents", tens[cents_tens], ones_and_teens[cents_ones]);

    return cents_string; 
}


// ========= DOLLARS_TO_STRING ============= //
// This function takes in the total dollars  //
// (represented by the digits remaining      //
// after the last two digits of the input    //
// are removed) and converts it to a text    //
// string. Returns a pointer to that string  //
// to the caller.                            //
// ========================================= //

char* dollars_to_string(long long int total_dollars) {
    
    static char dollars_string[BUFFER_SIZE]; 
    dollars_string[0] = '\0';
    
    static char* ones_and_teens[] = {
        "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", 
        "eighteen", "nineteen"      
    };

    static char* tens[] = {
        "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"      
    };

    static char* thousand_multiplier[] = {"", "thousand", "million", "billion"}; 

    int multiplier = 0;
    char current_segment[BUFFER_SIZE] = "";

    if(total_dollars == 0){
        dollars_string[0] = '\0'; 
        return dollars_string; 
    }

    if(total_dollars == 1){
        snprintf(dollars_string, BUFFER_SIZE, "one dollar"); 
        return dollars_string; 
    }

    while (total_dollars > 0){

        if(total_dollars % THOUSAND_MULTIPLE_SEPERATOR == 0 && multiplier > 0){
            total_dollars = total_dollars / THOUSAND_MULTIPLE_SEPERATOR;
            multiplier++;
            continue;
        }

        current_segment[0] = '\0';
        
        long long int dollar_hundreds = (total_dollars / DOUBLE_DIGIT_SEPERATOR) % DIGIT_SEPERATOR;
        long long int dollar_tens = (total_dollars / DIGIT_SEPERATOR) % DIGIT_SEPERATOR; 
        long long int dollar_ones = total_dollars % DIGIT_SEPERATOR;

        if(dollar_hundreds > 0)
            sprintf(current_segment + strlen(current_segment), "%s hundred ", ones_and_teens[dollar_hundreds]);
        
        if(dollar_tens == 1)
            sprintf(current_segment + strlen(current_segment), "%s ", ones_and_teens[dollar_ones + TEEN_INDEX_OFFSET]);
        
        if(dollar_tens > 1 && dollar_ones == 0)
            sprintf(current_segment + strlen(current_segment), "%s ", tens[dollar_tens]);

        if(dollar_tens > 1 && dollar_ones > 0)
            sprintf(current_segment + strlen(current_segment), "%s-%s ", tens[dollar_tens], ones_and_teens[dollar_ones]);
        
        if(dollar_tens == 0 && dollar_ones > 0)
            sprintf(current_segment + strlen(current_segment), "%s ", ones_and_teens[dollar_ones]);

        if (multiplier > 0) 
            sprintf(current_segment + strlen(current_segment), "%s ", thousand_multiplier[multiplier]);
        

        total_dollars = total_dollars / THOUSAND_MULTIPLE_SEPERATOR;
        multiplier++;

        prepend_string(dollars_string, current_segment);
    }

    strcat_s(dollars_string, BUFFER_SIZE, "dollars"); 
    return dollars_string; 
}

// ========= PREPEND_STRING ============= //
// This function takes in two strings,   //
// destination and source, and prepends  //
// the source string to the destination  //
// string.                               //
//                                       //
// This function is needed since the     //
// dollars_to_string function builds the //
// string in reverse order.              // 
// ===================================== //


void prepend_string(char* destination, char* segment_to_prepend) {

    char temp[BUFFER_SIZE];
    strcpy_s(temp, BUFFER_SIZE, destination);
    strcpy_s(destination, BUFFER_SIZE, segment_to_prepend);
    strcat_s(destination, BUFFER_SIZE, temp);
}

