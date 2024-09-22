# Need CMake 3.28.0
cmake_minimum_required (VERSION 3.28.0)

# This is the name of the repository
project ("test")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Set compiler warnings
if(MSVC)
    # TODO
else()

    # For clang
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Wpedantic -Weverything -Wno-declaration-after-statement -Ofast")

    # For GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Wpedantic -Wno-declaration-after-statement -O3")
endif()

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set for debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif()

# Find the log module
if ( NOT "${HAS_LOG}")
    
    # Add the log directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/log ${CMAKE_SOURCE_DIR}/build/log)

    # Let any parent project know that this project has log
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_LOG true PARENT_SCOPE)
        set(LOG_INCLUDE_DIR ${LOG_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")
    
    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SYNC true PARENT_SCOPE)
        set(SYNC_INCLUDE_DIR ${SYNC_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the array module
if ( NOT "${HAS_JSON}")
    
    # Add the array directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/json ${CMAKE_SOURCE_DIR}/build/json)

    # Let any parent project know that this project has array
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_JSON true PARENT_SCOPE)
        set(JSON_INCLUDE_DIR ${JSON_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the array module
if ( NOT "${HAS_ARRAY}")
    
    # Add the array directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/array ${CMAKE_SOURCE_DIR}/build/array)

    # Let any parent project know that this project has array
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_ARRAY true PARENT_SCOPE)
        set(ARRAY_INCLUDE_DIR ${ARRAY_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the dict module
if ( NOT "${HAS_DICT}")
    
    # Add the dict directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/dict ${CMAKE_SOURCE_DIR}/build/dict)

    # Let any parent project know that this project has dict
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_DICT true PARENT_SCOPE)
        set(DICT_INCLUDE_DIR ${DICT_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add the test project
if ( NOT "${HAS_TEST}")

    # Log
    message("[test] Adding test project")

    set (TEST_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the test project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_TEST true PARENT_SCOPE)
        set(TEST_INCLUDE_DIR ${TEST_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add source to this project's executable.
add_executable(test_example "main.c" "stack.c")
add_dependencies(test_example test json dict array hash_cache log sync)
target_include_directories(test_example PUBLIC ${TEST_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(test_example test json dict array hash_cache log sync)

# Add source to the library
add_library(test SHARED "test.c")
add_dependencies(test json dict array hash_cache log sync)
target_include_directories(test PUBLIC include ${TEST_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(test json dict array hash_cache log sync)
