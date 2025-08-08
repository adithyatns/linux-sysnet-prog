#include <stdio.h>
#include "fileio.h"
int read_file(const char*filename, char *buffer, size_t max_len)
{
    if(!filename || !buffer || max_len == 0)
        return -1;
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return -2;
    size_t byte_read = fread(buffer, 1, max_len-1, fp);
    if (byte_read == -1 ){
        return -3;
    }
    buffer[byte_read] = '\0';
    return byte_read;
}
