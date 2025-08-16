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
        FILE* fp = fopen(fname, "w");
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
    const char* content = "Hello, world!";
    FILE* fp = fopen(fname, "w");
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
    const char* test_filename = "testfile1.txt";

    int result = read_file(test_filename, buffer, sizeof(buffer));
    CHECK_EQUAL(-2, result);
    remove(test_filename);  // Clean up
}

TEST(FileIO, FileReadFail) {
    FILE* fp = fopen(fname, "w");
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
    const char* content = "Hello, world!";
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

    const char* data = "Test data";
    if (!fname) printf("fname is not null\n");
    int result = write_file(fname, data);  // Expect failure
    CHECK_EQUAL(-2, result);
}

/***************
 * files_exists
 *********************/

TEST_GROUP(FileIO_Exists){};

TEST(FileIO, Return1ForExistingRegularFile) {
    char p[256];
    snprintf(p, sizeof p, "/tmp/fe_%d.txt", getpid());
    FILE* f = fopen(p, "w");
    CHECK(f != NULL);
    fputs("x", f);
    fclose(f);

    CHECK_EQUAL(1, file_exists(p));

    remove(p);
}

TEST(FileIO_Exists, Returns1ForExistingDirectory) {
    char d[256];
    snprintf(d, sizeof d, "/tmp/fe_dir_%d", getpid());
    CHECK_EQUAL(0, mkdir(d, 0755));
    CHECK_EQUAL(1, file_exists(d));
    rmdir(d);
}

TEST(FileIO_Exists, Returns0ForMissing) {
    char p[256];
    snprintf(p, sizeof p, "/tmp/fe_missing_%d.txt", getpid());
    CHECK_EQUAL(0, file_exists(p));
}

TEST(FileIO_Exists, ReturnsMinus1ForNull) {
    CHECK_EQUAL(-1, file_exists(NULL));
}

/**********************
 * append_files
 *********************/
TEST_GROUP(FileIO_Append){};

static void read_back(const char* path, char* buf, size_t buflen) {
    FILE* f = fopen(path, "r");
    CHECK(f != NULL);
    size_t n = fread(buf, 1, buflen - 1, f);
    buf[n] = '\0';
    fclose(f);
}

TEST(FileIO_Append, AppendsToExistingFile) {
    char p[256];
    snprintf(p, sizeof p, "/tmp/app_%d.txt", getpid());
    FILE* f = fopen(p, "w");
    CHECK(f != NULL);
    fputs("Hello", f);
    fclose(f);

    CHECK_EQUAL(0, append_file(p, " World"));

    char buf[64] = {0};
    read_back(p, buf, sizeof buf);
    STRCMP_EQUAL("Hello World", buf);

    remove(p);
}

TEST(FileIO_Append, CreatesIfMissingAndWrites) {
    char p[256];
    snprintf(p, sizeof p, "/tmp/app_create_%d.txt", getpid());
    // ensure missing
    remove(p);

    CHECK_EQUAL(0, append_file(p, "New"));

    char buf[16] = {0};
    read_back(p, buf, sizeof buf);
    STRCMP_EQUAL("New", buf);

    remove(p);
}

TEST(FileIO_Append, FailsOnReadOnlyFile) {
    char p[256];
    snprintf(p, sizeof p, "/tmp/app_ro_%d.txt", getpid());
    FILE* f = fopen(p, "w");
    CHECK(f != NULL);
    fputs("X", f);
    fclose(f);

    // Make file read-only: appending should fail on most systems
    CHECK_EQUAL(0, chmod(p, 0444));

    int rc = append_file(p, "Y");
    CHECK(rc == -1);

    // restore perms so we can clean up
    chmod(p, 0644);
    remove(p);
}

/**********************
 * file_size
 *********************/

TEST_GROUP(FileIO_Size){};

TEST(FileIO_Size, RegularFileReturnsSize) {
    char p[256];
    snprintf(p, sizeof p, "/tmp/fs_%d.txt", getpid());
    FILE* f = fopen(p, "w");
    CHECK(f != NULL);
    fputs("abc", f);
    fclose(f);

    long sz = file_size(p, 0);
    CHECK(sz >= 3);

    remove(p);
}

TEST(FileIO_Size, MissingReturnsMinus1) {
    char p[256];
    snprintf(p, sizeof p, "/tmp/fs_missing_%d.txt", getpid());
    LONGS_EQUAL(-1, file_size(p, 0));
}

TEST(FileIO_Size, NullReturnsMinus1) {
    LONGS_EQUAL(-1, file_size(NULL, 0));
}

TEST(FileIO_Size, SymlinkFollowVsNoFollow) {
    char tgt[256], lnk[256];
    snprintf(tgt, sizeof tgt, "/tmp/fs_tgt_%d.txt", getpid());
    snprintf(lnk, sizeof lnk, "/tmp/fs_lnk_%d.txt", getpid());

    FILE* f = fopen(tgt, "w");
    CHECK(f != NULL);
    fputs("hello", f);
    fclose(f);

    CHECK_EQUAL(0, symlink(tgt, lnk));

    long nofollow = file_size(lnk, 0);  // lstat → link object size (>0)
    long follow = file_size(lnk, 1);    // stat  → target size (>=5)

    CHECK(nofollow > 0);
    CHECK(follow >= 5);

    unlink(lnk);
    remove(tgt);
}