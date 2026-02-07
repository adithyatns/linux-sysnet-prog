#ifndef MOCK_SYSCALLS_HPP
#define MOCK_SYSCALLS_HPP

#include <gmock/gmock.h>

// The Interface: Defines what system calls we want to control
class SyscallInterface {
public:
    virtual ~SyscallInterface() = default;
    virtual int open(const char* pathname, int flags, mode_t mode) = 0;
    virtual int close(int fd) = 0;
    virtual ssize_t write(int fd, const void* buf, size_t count) = 0;
};

// The Mock Class: Google Mock implements the interface here
class MockSyscalls : public SyscallInterface {
public:
    // This global pointer allows the C wrappers to find the active mock
    static MockSyscalls* instance;

    MOCK_METHOD(int, open, (const char* pathname, int flags, mode_t mode), (override));
    MOCK_METHOD(int, close, (int fd), (override));
    MOCK_METHOD(ssize_t, write, (int fd, const void* buf, size_t count), (override));
};

#endif // MOCK_SYSCALLS_HPP