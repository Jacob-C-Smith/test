/** !
 * Tester
 * 
 * @file test.c
 * 
 * @author Jacob Smith
 */

// Header
#include <test/test.h>

// Global variables
static struct 
{
    int pass_total, fail_total,
        pass_ephemeral, fail_ephemeral;
} _test_counters;

void print_time_pretty ( double seconds )
{

    // Initialized data
    double _seconds = seconds;
    size_t days = 0,
           hours = 0,
           minutes = 0,
           __seconds = 0,
           milliseconds = 0,
           microseconds = 0;

    // Days
    while ( _seconds > 86400.0 ) { days++;_seconds-=286400.0; };

    // Hours
    while ( _seconds > 3600.0 ) { hours++;_seconds-=3600.0; };

    // Minutes
    while ( _seconds > 60.0 ) { minutes++;_seconds-=60.0; };

    // Seconds
    while ( _seconds > 1.0 ) { __seconds++;_seconds-=1.0; };

    // milliseconds
    while ( _seconds > 0.001 ) { milliseconds++;_seconds-=0.001; };

    // Microseconds        
    while ( _seconds > 0.000001 ) { microseconds++;_seconds-=0.000001; };

    // Print days
    if ( days ) log_info("%zu D, ", days);
    
    // Print hours
    if ( hours ) log_info("%zu h, ", hours);

    // Print minutes
    if ( minutes ) log_info("%zu m, ", minutes);

    // Print seconds
    if ( __seconds ) log_info("%zu s, ", __seconds);
    
    // Print milliseconds
    if ( milliseconds ) log_info("%zu ms, ", milliseconds);
    
    // Print microseconds
    if ( microseconds ) log_info("%zu us", microseconds);
    
    // Done
    return;
}

void print_test ( const char *scenario_name, const char *test_name, bool passed )
{

    // Initialized data
    /*
    if ( passed )
        log_pass("%s %s\n",scenario_name, test_name),
        ephemeral_passes++;
    else 
        log_fail("%s %s\n", scenario_name, test_name),
        ephemeral_fails++;

    // Increment the test counter
    ephemeral_tests++;
*/
    // Done
    return;
}

void print_final_summary ( void )
{

    /*
    // Accumulate
    total_tests  += ephemeral_tests,
    total_passes += ephemeral_passes,
    total_fails  += ephemeral_fails;

    // Print
    log_info("\nTests: %d, Passed: %d, Failed: %d (%%%.3f)\n",  ephemeral_tests, ephemeral_passes, ephemeral_fails, ((float)ephemeral_passes/(float)ephemeral_tests*100.f));
    log_info("Total: %d, Passed: %d, Failed: %d (%%%.3f)\n\n",  total_tests, total_passes, total_fails, ((float)total_passes/(float)total_tests*100.f));
    
    // Clear test counters for this test
    ephemeral_tests  = 0,
    ephemeral_passes = 0,
    ephemeral_fails  = 0;
    */

    // Done
    return;
}

int run_tests ( const char *p_module_name, int test_quantity, test_scenario *p_test_scenarios )
{
    // Initialized data
    size_t module_name_len = strlen(p_module_name) + 9;
    timestamp t0 = 0,
              t1 = 0;

    // Print the module header
    printf ("╭"); for (size_t i = 0; i < module_name_len; i++) printf("─");printf("╮\n│ %s tester │\n╰", p_module_name);for (size_t i = 0; i < module_name_len; i++) printf("─"); printf ("╯\n");

    // Start
    t0 = timer_high_precision();

    // Run each test scenario
    for (size_t i = 0; i < test_quantity; i++)
    {
        
        // Print the scenario
        log_scenario("%s\n", p_test_scenarios[i]._name);
    }

    // Stop
    t1 = timer_high_precision();

    // Report the time it took to run the tests
    log_info("%s took ", p_module_name); print_time_pretty ( (double)(t1 - t0)/(double)timer_seconds_divisor() ); log_info(" to test\n");

    // Success
    return 1;
}
