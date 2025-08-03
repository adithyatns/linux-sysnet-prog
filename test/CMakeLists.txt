# test/CMakeLists.txt

file(GLOB TEST_SOURCES *.cpp)

add_executable(all_tests ${TEST_SOURCES})

# Ensure CppUTest and your own library are linked
target_link_libraries(all_tests PRIVATE
    sysnet
    CppUTest
)

# Add include paths (CppUTest and your own headers)
target_include_directories(all_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    $ENV{HOME}/cpputest/include
)

# Add the CppUTest library path
link_directories($ENV{HOME}/cpputest/lib)

# Register test binary
add_test(NAME AllTests COMMAND all_tests)
