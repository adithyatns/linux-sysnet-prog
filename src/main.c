#include "main.h"

#include <string.h>
#include <unistd.h>

int get_hostname(char *buffer, size_t len) {
    return gethostname(buffer, len);
}
