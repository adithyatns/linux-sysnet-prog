# File I/O API Specification

## API - file_exists

### Protoype

```c
int read_file(const char *path, char *buffer, size_t len)
```

### **Description:**

 Reads up to `len` bytes from file at `path` into `buffer`.  

### **Returns:**

- Number of bytes read
  `-1` on error.

---

## API - write_file

### Protoype

```c
int write_file(const char *path, const char *data, size_t len)
```

### **Description:**

Writes `len` bytes from `data` into file at `path`.  

### **Returns:**

- 0 on success
- -1 on error.

---

## API - file_exists

### Protoype

```c
 bool file_exists(const char *path)
 ```

### **Description**

 Checks if a file or directory exists at path. Returns true if accessible, false otherwise.

### **Parameters**

- path - Path to check

---

## API: append_file

### Prototype

```c
ssize_t append_file(const char *path, const void *buffer, size_t len);
```

### Description

Opens or creates a file for appending, writes the given data at the end.

### Parameters

- path — Target file
- buffer — Pointer to data
- len — Number of bytes to write

### Returns

- >=0 — Bytes written
- -1 — On error (errno set)

---

## API: file_size

### Prototype

```c
off_t file_size(const char *path, bool follow_symlinks);
```

### Description

Retrieves file size in bytes. Optionally follows symlinks.

### Parameters

- path — Path to file
- follow_symlinks — If true, uses stat; if false, uses lstat

### Returns

- >=0 — Size in bytes
- -1 — On error (errno set)

---
