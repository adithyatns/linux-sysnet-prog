include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)


# Create the test executable
add_executable(unit_tests 
    test_demo.cpp 
    mocks/mock_syscalls.cpp
)

target_include_directories(unit_tests PUBLIC mocks)

# Link everything together
target_link_libraries(unit_tests PRIVATE 
    ch04_lib              # Your Code
    GTest::gtest_main     # Google Test
    GTest::gmock          # Google Mock
)

# Apply the linker wrappers (The Mocking Magic)
target_link_options(unit_tests PRIVATE 
    -Wl,--wrap=open 
    -Wl,--wrap=close 
    -Wl,--wrap=write 
)

include(GoogleTest)

gtest_discover_tests(unit_tests)