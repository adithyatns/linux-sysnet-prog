# File IO Essentials

- Linux System APIs that operated on regular files
- these are ASCII text files, Binary data files, executables, and speified format files
- the book I am refering scope it explaination to the following
  - abstracted stream model
  - system level with system call
  - concept regarding I/O buffering, redirection, understanding open stream and file descriptor, mapping stream to a file descriptor

## Regular File IO

### stream

- A sequence of characters
- data structure used for stream in FILE structure
- we access the file decriptors via stream object (FILE *) and assign them to fd 0,1,2 - stdin, stdout, stderr
- general seqeunce fopend <-do file IO operations -> fclose
- these File I/O inlcude fwrite/fread, fprintf/fscanf and fputc/getc

[fopen](https://man7.org/linux/man-pages/man3/fopen.3.html)

- close after every open
  - int fclose(FILE *stream);
  - It's important to realize that closing a file has the underlying OS guarantee that it will synchronize the file's data content, which will ensure that all buffers

### I/O buffering

- for runtime optimization library will often use memory caches between library and underlying storage.
- this buffer is maitained by library
- it write till the buffer is full and then performs a one shot opeation to sync the file on storage
- this gives performance benifits as application will run faster, no overhead for each storage operation
- refer to virtual memory chapter
  