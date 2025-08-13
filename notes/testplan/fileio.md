# Test Plan: File I/O

## Objectives

- Validate correct reading and writing of files.
- Ensure error cases are handled gracefully.

## Positive Test Cases

1. Read existing file with known content.
2. Write file to valid location and verify content.

## Negative Test Cases

1. Read non-existent file.
2. Write to read-only file.
3. Read with insufficient buffer size.
