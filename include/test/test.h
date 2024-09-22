/** !
 * Tester
 * 
 * @file test.h
 * 
 * @author Jacob Smith
 */

// Header
#include <math.h>
#include <sync/sync.h>
#include <json/json.h>
#include <log/log.h>

// Set reallocator macros
// Set the reallocator for the dict module
#ifdef DICT_REALLOC
    #undef DICT_REALLOC
    #define DICT_REALLOC(p, sz) realloc(p, sz)
#endif

// Set the reallocator for the array module
#ifdef ARRAY_REALLOC
    #undef ARRAY_REALLOC
    #define ARRAY_REALLOC(p, sz) realloc(p, sz)
#endif

// Set the reallocator for the array module
#ifdef ARRAY_REALLOC
    #undef ARRAY_REALLOC
    #define ARRAY_REALLOC(p, sz) realloc(p, sz)
#endif

// Memory management macro
#ifndef TEST_REALLOC
#define TEST_REALLOC(p, sz) realloc(p,sz)
#endif

// Enumeration definitions
enum result_e
{
    zero     = 0,
    one      = 1,
    match    = 2,
    not_null = 3
};

// Structure definitions
struct test_scenario_s
{
    char _name[63+1];
    size_t cases_quantity;
    test_case _p_cases[];
};

struct test_case_s
{
    char _name[63+1];
    struct 
    {
        void *result;
        json_value *p_data;
    } expected;
};

struct test_module_s
{
    char _name[63+1];
    char *p_file_contents;
    json_value *p_value;
    dict *p_constants;
    size_t scenario_quantity;
    test_scenario _p_scenarios[];
};

// Type definitions
typedef enum result_e          result_t;
typedef struct test_case_s     test_case;
typedef struct test_scenario_s test_scenario;
typedef struct test_module_s   test_module;

// Forward declarations

// Log
/** !
 * Print the result of a single test
 * 
 * @param scenario_name the name of the scenario
 * @param test_name     the name of the test
 * @param passed        true if test passes, false if test fails
 * 
 * @return void
 */
void print_test ( const char *scenario_name, const char *test_name, bool passed );

/** !
 * Print a summary of the test scenario
 * 
 * @param void
 * 
 * @return void
 */
void print_final_summary ( void );

/** !
 * Print the time formatted in days, hours, minutes, seconds, miliseconds, microseconds
 * 
 * @param seconds the time in seconds
 * 
 * @return void
 */
void print_time_pretty ( double seconds );

/** !
 * Load a module tester from the file system
 * 
 * @param pp_test_module result
 * @param p_path         the path to the module tester
 * 
 * @return 1 on success, 0 on error
 */
int test_module_load ( test_module **pp_test_module, const char *p_path );

int run_tests ( test_module *p_test_module );