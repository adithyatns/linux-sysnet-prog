#include "CppUTest/TestHarness.h"
extern "C" {
#include "fileio.h"
}
#include <stdio.h>     // FILE operations
#include <string.h>    // snprintf()
#include <sys/stat.h>  // chmod()
#include <unistd.h>    // access(), getpid()

#define MAX_BUFFER_LEN 256U
TEST_GROUP(FileIO) {
    char buffer[MAX_BUFFER_LEN];
    char fname[MAX_BUFFER_LEN];

    void setup() {
        memset(buffer, 0, sizeof(buffer));
        // Create unique test file in /tmp
        snprintf(fname, sizeof(fname), "/tmp/testfile_%d.txt", getpid());

        // Create file for setup
        FILE *fp = fopen(fname, "w");
        CHECK_TEXT(fp != NULL, "Failed to create test file in setup");
        fprintf(fp, "initial");
        fclose(fp);
    }

    void teardown() {
        chmod(fname, 0644);  // restore write perms if changed
        remove(fname);       // delete test file
    }
};

TEST(FileIO, CanReadFileContent) {
    const char *content = "Hello, world!";
    FILE *fp = fopen(fname, "w");
    fprintf(fp, content);
    fclose(fp);

    int result = read_file(fname, buffer, strlen(content) + 1);
    CHECK(result > 0);
    STRCMP_EQUAL("Hello, world!", buffer);
}

// check for filename is null
TEST(FileIO, fileNameNullCheck) {
    int result = read_file(NULL, buffer, sizeof(buffer));
    CHECK(result == -1);
}

// check for buffer is null
TEST(FileIO, BufferNULLcheck) {
    int result = read_file(fname, NULL, sizeof(buffer));
    CHECK(result == -1);
}

// check for buffer is null
TEST(FileIO, FileDoesnotExit) {
    const char *test_filename = "testfile1.txt";

    int result = read_file(test_filename, buffer, sizeof(buffer));
    CHECK_EQUAL(-2, result);
    remove(test_filename);  // Clean up
}

TEST(FileIO, FileReadFail) {
    FILE *fp = fopen(fname, "w");
    fprintf(fp, "Hello, world!");
    fclose(fp);

    int result = read_file(fname, buffer, sizeof(buffer) * 2);
    CHECK_EQUAL(-3, result);
}

/*
Feature: write data to file
*/

/*
Scenario: Successful write
Given a valid filename and data
When the user calls write_file(filename, data)
Then the function returns 0 and the file contains the data
*/

TEST(FileIO, CanWriteFileContent) {
    const char *content = "Hello, world!";
    int result = write_file(fname, content);

    int rr = read_file(fname, buffer, strlen(content) + 1);
    CHECK_EQUAL(strlen(content), rr);
    STRCMP_EQUAL("Hello, world!", buffer);
}

/**
 * @brief Sceanario: File name Null or data
 *
 */

TEST(FileIO, WriteNULLFilenameFails) {
    int result = write_file(NULL, "Hello");
    CHECK_EQUAL(-1, result);
}

TEST(FileIO, WriteNULLdataFails) {
    int result = write_file("testfile.txt", NULL);
    CHECK_EQUAL(-1, result);
}

TEST(FileIO, WriteToUnwritableFileFails) {
    // Make sure file exists before chmod
    CHECK_TEXT(access(fname, F_OK) == 0, "File does not exist before chmod");

    // Set file to read-only
    int rc = chmod(fname, 0444);
    CHECK_TEXT(rc == 0, "chmod failed to set file to read-only");

    const char *data = "Test data";
    if (!fname) printf("fname is not null\n");
    int result = write_file(fname, data);  // Expect failure
    CHECK_EQUAL(-2, result);
}