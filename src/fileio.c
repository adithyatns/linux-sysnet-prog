#include "fileio.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
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

int file_exists(const char *path) {
    /*NULL check for path*/
    if (path == NULL) return -1;

    /* check if the file in path exist */
    if (access(path, F_OK) != 0) {
        perror("access()");
        printf("error: %s\n", strerror(errno));
        return 0;
    }
    return 1;
}

/**
 * @brief
 * Opens or creates a file for appending, writes the given data at the end.
 * Returns
 *  >=0 — Bytes written
 *  -1 — On error (errno set)
 * @param path
 * @param buffer
 * @return int
 */
int append_file(const char *path, const void *buffer) {
    if (path == NULL || buffer == NULL) {
        return -1;
    }
    FILE *fd = fopen(path, "a");
    if (!fd) {
        perror("fopen()");
        return -1;
    }
    if (fputs((const char *)buffer, fd) == EOF) {
        fclose(fd);
        return -1;
    }
    fclose(fd);
    return 0;
}

/**
 * @brief Retrieves file size in bytes. Optionally follows symlinks.
 * >=0 — Size in bytes
 * -1 — On error (errno set)
 * @param path
 * @param follow_symlinks
 * @return long
 */
long file_size(const char *path, bool follow_symlinks) {
    if (path == NULL) return -1;
    struct stat file_state;
    int rc = follow_symlinks ? stat(path, &file_state) : lstat(path, &file_state);
    if (rc != 0) {
        return -1;
    }

    return file_state.st_size;
}