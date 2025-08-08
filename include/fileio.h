#ifndef FILEIO_H
#define FILEIO_H
#include <stddef.h> // for size_t
int read_file(const char *filename, char* buffer, size_t max_len);
#endif

