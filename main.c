/** !
 * tester example
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
    test_module _stack_tester = 
    {
        ._name = "stack"
    };

    // Success
    return run_tests(&_stack_tester) ? EXIT_SUCCESS : EXIT_FAILURE;
}
