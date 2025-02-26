#include <string.h>
#include <stdio.h>
#include "value_to_string_conversions.h"
#include "cache.h"
#include "constants.h"

// ==============FUNCTION POINTERS================//

to_string_fnc assigned_large_provider = NULL;
to_string_fnc assigned_small_provider = NULL;
to_string_fnc original_large_provider = NULL;
to_string_fnc original_small_provider = NULL;

// ============= PROTOTYPES ======================//

char *number_to_string(long long int money_value_as_integer);

// ================== MAIN ======================== //
// This program reads integer input representing    //
// values of money (dollars and cents) and converts //
// them into words. Values less than or equal to    //
// 150000 ($1500) are memoized                      //
// ================================================ //

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        printf("Unexpected argument provided");
        return 1;
    };

    assigned_large_provider = dollars_to_string;
    assigned_small_provider = cents_to_string;

    initialize_cache(dollars_to_string, cents_to_string);

    char buffer[BUFFER_SIZE];
    long long int money_value_as_integer = 0;
    int parsed_char_count;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        if (sscanf_s(buffer, "%lld%n", &money_value_as_integer, &parsed_char_count) != 1 || buffer[parsed_char_count] != '\0')
        {
            printf("Failed to provide a valid integer\n");
            continue;
        }

        if (money_value_as_integer < 0)
        {
            printf("Invalid input. Enter a positive value.\n");
            continue;
        }

        char *result = number_to_string(money_value_as_integer);
        printf("%lld = %s\n", money_value_as_integer, result);
    }

    // DEBUG
    // print_cache();
    free_cache(); 

    return 0;
}

// ========= NUMBER_TO_STRING ============= //
// This function takes in the value input  //
// and parses it into dollars and cents    //
// and passes each segment to its          //
// respective conversion function          //
//                                         //
// ======================================= //

char *number_to_string(long long int money_value_as_integer)
{

    static char result[BUFFER_SIZE];
    result[0] = '\0';

    if (money_value_as_integer == 0)
    {
        strcpy_s(result, BUFFER_SIZE, "zero dollars and zero cents");
        return result;
    }

    long long int total_dollars = money_value_as_integer / DOUBLE_DIGIT_SEPERATOR;
    long long int total_cents = money_value_as_integer % DOUBLE_DIGIT_SEPERATOR;

    char *dollars = (*assigned_large_provider)(total_dollars);
    char *cents = (*assigned_small_provider)(total_cents);

    if (money_value_as_integer < MINIMUM_FOR_DOLLARS)
    {
        strcpy_s(result, BUFFER_SIZE, cents);
        return result;
    }

    if (money_value_as_integer >= MINIMUM_FOR_DOLLARS && total_cents == 0)
    {
        strcpy_s(result, BUFFER_SIZE, dollars);
        return result;
    }

    if (money_value_as_integer >= MINIMUM_FOR_DOLLARS && total_cents > 0)
    {
        sprintf(result, "%s and %s", dollars, cents);
    }

    return result;
}
