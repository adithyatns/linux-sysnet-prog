// ch04_file_io/demo_logic.c
#include "demo_logic.h"
#include <fcntl.h>  // For open() flags
#include <unistd.h> // For write(), close()
#include <stdio.h>  // For perror() only

int write_data_to_file(const char* filename, const char* data, int len) {
    // STUB: Fails intentionally to prove the test works
       // 1. OPEN (System Call)
    // O_WRONLY: Write only
    // O_CREAT: Create if not exists
    // 0644: File permissions (rw-r--r--)
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);

    if (fd < 0) {
        perror("Open failed");
        return -1;
    }

    // 2. WRITE (System Call)
    // Direct write to the file descriptor (no buffering)
    //char *msg = "Hello from Kernel Space!\n";
    // Note: We must explicitly state how many bytes to write
    int bytes_written = write(fd, data, len); 
    if(bytes_written < 0) {
        perror("Write failed");
        // Even if write fails, we should still close the file descriptor to avoid leaks
        close(fd);
        return -1;
    }
    if (bytes_written < len)
    {
        fprintf(stderr, "Partial write: only %d of %d bytes written\n", bytes_written, len);
        // Handle partial write if necessary (e.g., retry logic), but for this demo, we just report it.
    }
    
    // 3. CLOSE (System Call)
    close(fd);

    return bytes_written; // Return the number of bytes written, or -1 on error
}