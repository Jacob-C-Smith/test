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

size_t load_file ( const char *path, void *buffer, bool binary_mode )
{

    // Argument checking 
    if ( path == 0 ) goto no_path;

    // Initialized data
    size_t  ret = 0;
    FILE   *f   = fopen(path, (binary_mode) ? "rb" : "r");
    
    // Check if file is valid
    if ( f == NULL ) goto invalid_file;

    // Find file size and prep for read
    fseek(f, 0, SEEK_END);
    ret = (size_t) ftell(f);
    fseek(f, 0, SEEK_SET);
    
    // Read to data
    if ( buffer ) 
        ret = fread(buffer, 1, ret, f);

    // The file is no longer needed
    fclose(f);
    
    // Success
    return ret;

    // Error handling
    {

        // Argument errors
        {
            no_path:
                #ifndef NDEBUG
                    log_error("[json] Null path provided to function \"%s\n", __FUNCTION__);
                #endif

            // Error
            return 0;
        }

        // File errors
        {
            invalid_file:
                #ifndef NDEBUG
                    printf("[Standard library] Failed to load file \"%s\". %s\n",path, strerror(errno));
                #endif

            // Error
            return 0;
        }
    }
}

result_t load_json ( json_value **pp_value, char *test_file, char **free_me )
{

    // Initialized data
    size_t    file_len = load_file(test_file, 0, false);
    char     *file_buf = malloc( (file_len + 1) * sizeof(char));
    result_t  r        = 0; 
    
    // Error check
    if ( file_buf == (void *) 0 ) goto no_mem; 

    // Load the file
    load_file(test_file, file_buf, false);

    // Parse JSON
    r = (result_t) json_value_parse(file_buf, 0, pp_value);

    // Return a pointer to the caller with the allocated memory
    *free_me = file_buf;

    // Success
    return r;

    // Error handling
    {
        
        // Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					log_error("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
    }
}

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

int test_module_load ( test_module **pp_test_module, const char *p_path )
{

    // Argument check
    //

    // Initialized data
    test_module *p_test_module = { 0 };

    // Load the test module
    load_json(&p_test_module->p_value, p_path, &p_test_module->p_file_contents);

    // Type check
    if ( p_test_module->p_value->type != JSON_VALUE_OBJECT ) goto wrong_type;

    // Parse the test module
    {

        // Initialized data
        dict        *p_dict      = 0;
        json_value  *p_scenarios = 0,
                    *p_constants = 0;

        // Store the object
        p_dict = p_test_module->p_value->object;

        // Store the scenarios
        p_scenarios = dict_get(p_dict, "scenarios");

        // Store the constants
        p_constants = dict_get(p_dict, "constants");

        // Type check
        if ( p_constants->type != JSON_VALUE_OBJECT ) goto wrong_type;

        // Store the constants
        p_test_module->p_constants = p_constants->object;

    }

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        //

        // Type errors
        {
            wrong_type:
                return 0;
        }
    }
}

int run_tests ( test_module *p_test_module )
{

    // Initialized data
    size_t module_name_len = strlen(p_test_module->_name) + 9;
    timestamp t0 = 0,
              t1 = 0;

    // Print the module header
    printf ("╭"); for (size_t i = 0; i < module_name_len; i++) printf("─");printf("╮\n│ %s tester │\n╰", p_test_module->_name);for (size_t i = 0; i < module_name_len; i++) printf("─"); printf ("╯\n");

    // Start
    t0 = timer_high_precision();

    
    // Stop
    t1 = timer_high_precision();

    // Report the time it took to run the tests
    log_info("%s took ", p_test_module->_name); print_time_pretty ( (double)(t1 - t0)/(double)timer_seconds_divisor() ); log_info(" to test\n");

    // Success
    return 1;
}
