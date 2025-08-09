# Development Workflow

This document describes the repeatable steps for developing, testing, and committing new features or APIs in this project.

## Plan the API
- Decide function name, parameters, and return type.
- Example:
```c
int read_file(const char *filename, char *buffer, size_t size);
```

## Write the Header
- Add the function declaration to the appropriate header file in `include/`.
- Example:
```c
// include/fileio.h
#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h> // for size_t

int read_file(const char *filename, char *buffer, size_t size);

#endif
```

## Write the Unit Test First (TDD)
- Create or modify a test file in `test/`.
- Include the header and write a failing test first.
- Example:
```cpp
#include "CppUTest/TestHarness.h"
#include "fileio.h"

TEST_GROUP(FileIO) {};

TEST(FileIO, CanReadFile) {
    char buffer[256] = {0};
    int result = read_file("test_data.txt", buffer, sizeof(buffer));
    CHECK_EQUAL(0, result);
    STRCMP_EQUAL("Hello\n", buffer);
}
```

## Write the Implementation
- Implement the function in `src/`.
- Example:
```c
#include "fileio.h"
#include <stdio.h>

int read_file(const char *filename, char *buffer, size_t size) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return -1;
    size_t read_bytes = fread(buffer, 1, size - 1, fp);
    buffer[read_bytes] = '\0';
    fclose(fp);
    return 0;
}
```

## Build
- Build the project with CMake:
```bash
cmake --build build
```

## Run Unit Tests
- Run tests with CTest:
```bash
ctest --output-on-failure
```

## Run Static Analysis & Formatting
- Run pre-commit checks (formats + clang-tidy):
```bash
pre-commit run --all-files
```
- This will format code with clang-format and run clang-tidy on `.c/.cpp/.h` files.

## Refactor if Needed
- Fix warnings and improve code readability.
- Make commits small and focused.

## Commit
- Stage and commit changes:
```bash
git add .
git commit -m "Add read_file API and tests"
```

## Push to GitHub
- Push your branch or main:
```bash
git push origin main
```
- GitHub Actions will run automatically and confirm tests pass in CI.

## Update Documentation
- Add usage examples to `README.md`.
- Write notes in your study log (PARA method).

## Notes
- Always write tests first before implementing the function.
- Run pre-commit before every commit to ensure consistent formatting and code quality.
- Keep commits focused on one feature or fix at a time.
