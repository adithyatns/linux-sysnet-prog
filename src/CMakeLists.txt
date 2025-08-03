file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS *.c)
add_library(sysnet STATIC ${SRC_FILES})
target_include_directories(sysnet PUBLIC ${CMAKE_SOURCE_DIR}/include)

