#include "mock_syscalls.hpp"
#include <cstdarg>
#include <fcntl.h>

// Initialize the global pointer to nullptr
MockSyscalls* MockSyscalls::instance = nullptr;

extern "C" {
    // 1. Declare the "real" functions (optional, if you want to fall back to them)
    // We don't strictly need them if we mock everything, but it's good practice.
    int __real_open(const char* pathname, int flags, ...);
    int __real_close(int fd);
    ssize_t __real_write(int fd, const void* buf, size_t count);

    // 2. The Wrapper for open()
    // NOTE: open() is variadic (it takes an optional 3rd argument for mode).
    int __wrap_open(const char* pathname, int flags, ...) {
        mode_t mode = 0;
        if (flags & O_CREAT) {
            va_list args;
            va_start(args, flags);
            mode = va_arg(args, mode_t);
            va_end(args);
        }

        if (MockSyscalls::instance) {
            return MockSyscalls::instance->open(pathname, flags, mode);
        }
        return __real_open(pathname, flags, mode);
    }

    // 3. The Wrapper for close()
    int __wrap_close(int fd) {
        if (MockSyscalls::instance) {
            return MockSyscalls::instance->close(fd);
        }
        return __real_close(fd);
    }

    // 4. The Wrapper for write()
    ssize_t __wrap_write(int fd, const void* buf, size_t count) {
        if (MockSyscalls::instance) {
            return MockSyscalls::instance->write(fd, buf, count);
        }
        return __real_write(fd, buf, count);
    }
}