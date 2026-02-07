cmake_minimum_required(VERSION 3.14)
project(LinuxSysNetProg C CXX)

set(CMAKE_CXX_STANDARD 14)

# 1. Define the library for your Chapter 4 logic
# This allows us to link the logic to BOTH the app and the tests
add_library(ch04_lib STATIC ch04_file_io/demo_logic.c)
target_include_directories(ch04_lib PUBLIC ch04_file_io include)

# 2. Build the main application (The regular binary)
#add_executable(syscall_demo ch04_file_io/syscall_demo.c)
#target_link_libraries(syscall_demo PRIVATE ch04_lib)

# 3. Enable Testing and add the test subdirectory
enable_testing()
add_subdirectory(test)