#include "value_to_string_conversions.h"

// ==============FUNCTION POINTERS================//

string_conversion_fnc dollar_provider;
string_conversion_fnc cent_provider; 
string_conversion_fnc original_cent_provider; 
string_conversion_fnc original_dollar_provider;

// ============= PROTOTYPES ======================//

char* number_to_string(long long int money_value_as_integer); 

// ================== MAIN ======================== //
// This program reads integer input representing    //
// values of money (dollars and cents) and converts //
// them into words. Values less than or equal to    //
// 150000 ($1500) are memoized                      // 
// ================================================ //

int main(int argc, char *argv[]) {

    if(argc > 1){
        printf("Unexpected argument provided"); 
        return 1; 
    };
    
    dollar_provider = cached_dollars; 
    cent_provider = cached_cents; 
    original_cent_provider =  cents_to_string; 
    original_dollar_provider = dollars_to_string; 

    initialize_cache();

    char buffer[BUFFER_SIZE]; 
    long long int money_value_as_integer = 0; 
    int parsed_char_count; 

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        
        if (sscanf_s(buffer, "%lld%n", &money_value_as_integer, &parsed_char_count) != 1 || buffer[parsed_char_count] != '\0'){
            printf("Failed to provide a valid integer\n");
            continue; 
        }

        if(money_value_as_integer < 0){
            printf("Invalid input. Enter a positive value.\n");
            continue; 
        }

        char* result = number_to_string(money_value_as_integer); 
        printf("%lld = %s\n", money_value_as_integer, result); 
    }

    // DEBUG
    // print_cache(); 
    
    return 0;
}

// ========= NUMBER_TO_STRING ============= //
// This function takes in the value input  //
// and parses it into dollars and cents    //
// and passes each segment to its          //
// respective conversion function          //
//                                         // 
// ======================================= //

char* number_to_string(long long int money_value_as_integer) {
    
    static char result[BUFFER_SIZE];
    result[0] = '\0';  

    if (money_value_as_integer == 0)
    {
        strcpy_s(result, BUFFER_SIZE, "zero dollars and zero cents");
        return result; 
    }

    long long int total_dollars = money_value_as_integer / DOUBLE_DIGIT_SEPERATOR; 
    long long int total_cents = money_value_as_integer % DOUBLE_DIGIT_SEPERATOR; 

    char* dollars = (*dollar_provider)(total_dollars); 
    char* cents = (*cent_provider)(total_cents);

    if (money_value_as_integer < MINIMUM_FOR_DOLLARS) {  
        strcpy(result, cents); 
        return result; 
    }

    if (money_value_as_integer >= MINIMUM_FOR_DOLLARS && total_cents == 0) {
        strcpy(result, dollars);  
        return result;
    }

    if(money_value_as_integer >= MINIMUM_FOR_DOLLARS && total_cents > 0){
        sprintf(result, "%s and %s", dollars, cents);   
    }

    return result;
}


