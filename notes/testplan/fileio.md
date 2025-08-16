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

### Tests: file_exists

- **Positive cases**
  - Existing regular file
  - Existing directory
  - Existing symlink to file
- **Negative cases**
  - Non-existent file
  - Null path
  - Empty path

---

### Tests: append_file

- **Positive cases**
  - Append to existing file (verify content grows)
  - Append to new file (verify content matches input)
- **Negative cases**
  - Unwritable path (read-only dir)
  - Null buffer with non-zero length
  - Zero-length write (should not modify file)
  - Disk full simulation (if possible)

---

### Tests: file_size

- **Positive cases**
  - Correct size for regular file
  - Symlink with follow=true
  - Symlink with follow=false
- **Negative cases**
  - Non-existent file
  - Null path
  - Permission denied
