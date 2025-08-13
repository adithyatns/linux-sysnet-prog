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
