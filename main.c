/** !
 * tester library example
 * 
 * @file main.c
 *
 * @author Jacob Smith
*/

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// log module
#include <log/log.h>

// test module
#include <test/test.h>

// stack module
#include <stack/stack.h>

// Entry point
int main ( int argc, const char* argv[] )
{

    // Supress compiler warnings
    (void) argc;
    (void) argv;

    // Initialized data
    test_scenario _test_scenarios[] = 
    {
        { 
            ._name = "empty"
        },
        { 
            ._name = "empty_pushA_A"
        },
        { 
            ._name = "A_pop_empty"
        },
        { 
            ._name = "A_pushB_AB"
        },
        { 
            ._name = "AB_pop_A"
        },
        { 
            ._name = "AB_pushC_ABC"
        },
        { 
            ._name = "ABC_pop_AB"
        }
    };

    // Success
    return ( run_tests ( "stack", 7, _test_scenarios ) == 0 ) ? EXIT_FAILURE : EXIT_SUCCESS;
}
