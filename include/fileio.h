#ifndef FILEIO_H
#define FILEIO_H
#include <stdbool.h>
#include <stddef.h>  // for size_t
int read_file(const char* filename, char* buffer, size_t max_len);
int write_file(const char* filename, const char* buffer);
int file_exists(const char* path);
int append_file(const char* path, const void* buffer);
long file_size(const char* path, bool follow_symlinks);
#endif
