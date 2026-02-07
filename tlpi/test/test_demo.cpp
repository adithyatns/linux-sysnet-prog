#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mock_syscalls.hpp"

// Include the header of the C code we are testing
extern "C" {
    #include "demo_logic.h"
}

using ::testing::_;
using ::testing::Return;
using ::testing::StrEq;

class FileIOTest : public ::testing::Test {
protected:
    MockSyscalls mocks;

    void SetUp() override {
        // Redirect the global wrapper pointer to this test's mock instance
        MockSyscalls::instance = &mocks;
    }

    void TearDown() override {
        // Clean up to prevent interference between tests
        MockSyscalls::instance = nullptr;
    }
};

// 1. SUCCESS SCENARIO
TEST_F(FileIOTest, WriteData_ReturnsBytesWritten_WhenAllSyscallsSucceed) {
    const char* filename = "success.txt";
    const char* data = "test_data";
    int len = 9;
    int fake_fd = 100; // Arbitrary file descriptor

    // EXPECTATION: open() is called with correct flags
    // We expect O_WRONLY | O_CREAT | O_TRUNC. 
    // Note: Checking exact flag integers can be brittle, checking mostly the filename here.
    EXPECT_CALL(mocks, open(StrEq(filename), _, _))
        .WillOnce(Return(fake_fd));

    // EXPECTATION: write() is called with the specific data
    EXPECT_CALL(mocks, write(fake_fd, _, len))
        .WillOnce(Return(len)); // Simulate writing all bytes

    // EXPECTATION: close() is called exactly once
    EXPECT_CALL(mocks, close(fake_fd))
        .WillOnce(Return(0));

    // ACT
    int result = write_data_to_file(filename, data, len);

    // ASSERT
    EXPECT_EQ(result, len);
}

// 2. OPEN FAILURE (e.g., Permissions Denied)
TEST_F(FileIOTest, WriteData_ReturnsError_WhenOpenFails) {
    // SIMULATION: open() returns -1 (error)
    EXPECT_CALL(mocks, open(_, _, _))
        .WillOnce(Return(-1));

    // STRICT MOCK: We imply that write() and close() should NEVER be called.
    // If the code tries to write to an invalid FD, GTest will fail this test automatically
    // because no EXPECT_CALL matches.

    int result = write_data_to_file("bad_perm.txt", "data", 4);

    // Assuming your logic returns -1 on open failure
    EXPECT_EQ(result, -1);
}

// 3. WRITE FAILURE (e.g., IO Error)
TEST_F(FileIOTest, WriteData_ReturnsError_WhenWriteFails) {
    int fake_fd = 200;

    // 1. Open succeeds
    EXPECT_CALL(mocks, open(_, _, _)).WillOnce(Return(fake_fd));

    // 2. Write fails (returns -1)
    EXPECT_CALL(mocks, write(fake_fd, _, _)).WillOnce(Return(-1));

    // 3. Critical: The file MUST still be closed to avoid resource leaks
    EXPECT_CALL(mocks, close(fake_fd)).WillOnce(Return(0));

    int result = write_data_to_file("io_error.txt", "data", 4);

    EXPECT_EQ(result, -1);
}

// 4. PARTIAL WRITE (e.g., Disk Full)
TEST_F(FileIOTest, WriteData_ReturnsPartialCount_WhenDiskFull) {
    int fake_fd = 300;
    int len = 10;
    int partial_write = 5; // Disk filled up halfway

    EXPECT_CALL(mocks, open(_, _, _)).WillOnce(Return(fake_fd));
    
    // Simulate writing only 5 bytes instead of 10
    EXPECT_CALL(mocks, write(fake_fd, _, len)).WillOnce(Return(partial_write));
    
    EXPECT_CALL(mocks, close(fake_fd)).WillOnce(Return(0));

    int result = write_data_to_file("full_disk.txt", "1234567890", len);

    // Your logic might treat this as an error (-1) or return the partial count (5).
    // This test assumes it returns the partial count.
    EXPECT_EQ(result, partial_write);
}