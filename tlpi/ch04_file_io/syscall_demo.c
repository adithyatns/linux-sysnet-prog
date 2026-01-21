#include <fcntl.h>  // For open() flags
#include <unistd.h> // For write(), close()
#include <stdio.h>  // For perror() only

int main() {
    // 1. OPEN (System Call)
    // O_WRONLY: Write only
    // O_CREAT: Create if not exists
    // 0644: File permissions (rw-r--r--)
    int fd = open("test_file.txt", O_WRONLY | O_CREAT, 0644);

    if (fd < 0) {
        perror("Open failed");
        return 1;
    }

    // 2. WRITE (System Call)
    // Direct write to the file descriptor (no buffering)
    char *msg = "Hello from Kernel Space!\n";
    // Note: We must explicitly state how many bytes to write
    int bytes_written = write(fd, msg, 25); 

    // 3. CLOSE (System Call)
    close(fd);

    return 0;
}
