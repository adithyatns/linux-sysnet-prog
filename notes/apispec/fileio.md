# File I/O API Specification

## `int read_file(const char *path, char *buffer, size_t len)`

**Description:** Reads up to `len` bytes from file at `path` into `buffer`.  
**Returns:** Number of bytes read, or `-1` on error.

---

## `int write_file(const char *path, const char *data, size_t len)`

**Description:** Writes `len` bytes from `data` into file at `path`.  
**Returns:** 0 on success, `-1` on error.
