#include "CppUTest/TestHarness.h"
extern "C"{
#include "fileio.h"
}
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_LEN 256U
TEST_GROUP(FileIO) {
    char buffer[MAX_BUFFER_LEN];

    void setup() {
        memset(buffer, 0, sizeof(buffer));
    }
};

TEST(FileIO, CanReadFileContent) {
    const char *test_filename = "testfile.txt";
    FILE *fp = fopen(test_filename, "w");
    fprintf(fp, "Hello, world!");
    fclose(fp);

    int result = read_file(test_filename, buffer, sizeof(buffer));
    CHECK(result > 0);
    STRCMP_EQUAL("Hello, world!", buffer);

    remove(test_filename); // Clean up
}
