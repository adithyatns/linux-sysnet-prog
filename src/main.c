#include <unistd.h>
#include <string.h>
#include "main.h"

int get_hostname(char *buffer, size_t len) {
 return gethostname(buffer, len);
}


