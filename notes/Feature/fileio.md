# File I/O Features

## Feature: Read from File

**Scenario:** Read a file successfully  

- **Given** a file exists with known content  
- **When** I call `read_file()` with a valid buffer and length  
- **Then** the content should match the file contents  

**Scenario:** File does not exist  

- **Given** no file at the given path  
- **When** I call `read_file()`  
- **Then** it should return `-1` and set an error code  

---

## Feature: Write to File

**Scenario:** Write a file successfully  

- **Given** I have a writable path  
- **When** I call `write_file()` with content and length  
- **Then** the file should be created and contain that content  

**Scenario:** Write fails due to permissions

- **Given** a file exists but is read-only
- **When** I call `write_file()`  
- **Then** it should return `-1` and set the correct error codei

## Feature: File Exist (`file_exist`)

As a developer, I want to check if a file or directory exist,
So that I can decide whether to read, write or create it

- **Sceanario**

  - File exists (regular file) -> returns true
  - Directory exists -> returns true
  - Symlinks exist -> returns true
  - File does not exist -> returns  false
  - Path is null or empty -> return false

---

## Feature : `append_file`

As a developer, I want to append data to end of the file, So that I can preserver existing content while adding new logs or entries.

- **Sceanario**

  - File exists, append succedded -> returns number of bytes wrtiten
  - File does not exist
  - does not have right permission to write on file
  - buffer is empty
  - Disk full or write erro -> return -1 , sets errno

---

## Feature: File size (`file_size`)

As a developer,
I want to get the size of a file in bytes,
So that I can validate file contents or allocate correct buffers.

- **Scenarios**

  - File exists (regular file) → returns correct size
  - Symlink → returns target file size (stat) or link size (lstat)
  - File does not exist → returns -1, sets errno
  - Path is null → returns -1, sets errno
  - Directory path → returns size from stat (system-dependent)
  