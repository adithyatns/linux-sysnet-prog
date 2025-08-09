#include "fileio.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // access(), getpid()

int read_file(const char *filename, char *buffer, size_t max_len) {
    if (!filename || (!buffer && (max_len > 0)) || max_len == 0) {
        perror("problem in parameter passed to function");
        return -1;
    }
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("problem in opening file");
        return -2;
    }
    size_t byte_read = fread(buffer, 1, max_len - 1, fp);
    if (byte_read != (max_len - 1)) {
        perror("problem in fread file");
        fclose(fp);
        return -3;
    }
    buffer[byte_read] = '\0';

    fclose(fp);
    return byte_read;
}

int write_file(const char *filename, const char *buffer) {
    int written_bytes;
    FILE *fp = NULL;

    if ((filename == NULL) || (buffer == NULL)) {
        perror("NULL pointer passed issue");
        return -1;
    }
    if (access(filename, W_OK) != 0) return -2;

    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("fopen fail");
        return -2;
    }

    written_bytes = fwrite(buffer, 1, strlen(buffer), fp);
    if (written_bytes != strlen((buffer))) {
        perror("fwrite failed");
        fclose(fp);
        return -3;
    }

    fclose(fp);
    return written_bytes;
}