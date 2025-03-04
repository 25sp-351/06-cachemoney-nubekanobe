#include <string.h>
#include <stdio.h>
#include <dlfcn.h>
#include "value_to_string_conversions.h"
#include "cache.h"
#include "constants.h"

// ============= PROTOTYPES ======================//
char *number_to_string(long long int money_value_as_integer, provider_set providers);
set_provider_fnc load_cache_module(const char *module_path); 

// ================== MAIN ======================== //
// This program reads integer input representing    //
// values of money (dollars and cents) and converts //
// them into words. Values less than or equal to    //
// 150000 ($1500) are memoized                      //
// ================================================ //

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [libcache.so]\n", argv[0]);
        return 1;
    }

    provider_set providers = {
        providers.large_values_provider = dollars_to_string,
        providers.small_values_provider = cents_to_string
    }; 
    
    if (argc == 2) {

        set_provider_fnc set_provider = load_cache_module(argv[1]);
        if (set_provider) {
            set_provider(&providers);
        } else {
            fprintf(stderr, "Failed to set cache provider from module.\n");
            return 1;
        }
    }

    char buffer[BUFFER_SIZE];
    long long int money_value_as_integer = 0;
    int parsed_char_count;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        if (sscanf(buffer, "%lld%n", &money_value_as_integer, &parsed_char_count) != 1 || buffer[parsed_char_count] != '\0')
        {
            printf("Failed to provide a valid integer\n");
            continue;
        }

        if (money_value_as_integer < 0)
        {
            printf("Invalid input. Enter a positive value.\n");
            continue;
        }

        char *result = number_to_string(money_value_as_integer, providers);
        printf("%lld = %s\n", money_value_as_integer, result);
    } 


    return 0;
}

// ========= NUMBER_TO_STRING ============= //
// This function takes in the value input  //
// and parses it into dollars and cents    //
// and passes each segment to its          //
// respective conversion function          //
//                                         //
// ======================================= //

char *number_to_string(long long int money_value_as_integer, provider_set providers)
{

    static char result[BUFFER_SIZE];
    result[0] = '\0';

    if (money_value_as_integer == 0)
    {
        strcpy(result, "zero dollars and zero cents");
        return result;
    }

    long long int total_dollars = money_value_as_integer / DOUBLE_DIGIT_SEPERATOR;
    long long int total_cents = money_value_as_integer % DOUBLE_DIGIT_SEPERATOR;

    char *dollars = (providers.large_values_provider)(total_dollars);
    char *cents = (providers.small_values_provider)(total_cents);

    if (money_value_as_integer < MINIMUM_FOR_DOLLARS)
    {
        strcpy(result, cents);
        return result;
    }

    if (money_value_as_integer >= MINIMUM_FOR_DOLLARS && total_cents == 0)
    {
        strcpy(result, dollars);
        return result;
    }

    if (money_value_as_integer >= MINIMUM_FOR_DOLLARS && total_cents > 0)
    {
        sprintf(result, "%s and %s", dollars, cents);
    }

    return result;
}


// ========= LOAD_CACHE_MODULE =========== //
// Loads the cache module and returns the  //
// function pointer to set_provider.       //
// ======================================= //


set_provider_fnc load_cache_module(const char *module_path) {
    void* handle = dlopen(module_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Failed to load library: %s\n", dlerror());
        return NULL;
    }

    set_provider_fnc set_provider = (set_provider_fnc) dlsym(handle, "set_provider");
    if (!set_provider) {
        fprintf(stderr, "Failed to load function 'set_provider': %s\n", dlerror());
        dlclose(handle);
        return NULL;
    }

    return set_provider;
}