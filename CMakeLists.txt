cmake_minimum_required(VERSION 3.14)
project(LabWork)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB hdrs "*.h*") 
if(hdrs)
    add_custom_target(include_headers SOURCES ${hdrs})
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(run_tests 
    test/test_main.cpp 
    test/test_stack.cpp 
    test/test_queue.cpp
)

target_include_directories(run_tests PRIVATE .)

target_link_libraries(run_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)

add_executable(solve_task 
    app/main_task.cpp 
)

target_include_directories(solve_task PRIVATE .)