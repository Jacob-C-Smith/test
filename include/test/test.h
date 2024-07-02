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
#include <log/log.h>

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

};

struct test_module_s
{
    char _name[63+1];

};

// Type definitions
typedef enum result_e result_t;
typedef struct test_scenario_s test_scenario;
typedef struct test_module_s test_module;

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

int run_tests ( const char *p_module_name, int test_quantity, test_scenario *p_test_scenarios );