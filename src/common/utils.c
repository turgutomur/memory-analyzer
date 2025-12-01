#include "utils.h"
#include <stdio.h>

void format_size(size_t size, char *output) {
    if (size < 1024) {
        sprintf(output, "%zu Bytes", size);
    } else {
        sprintf(output, "%zu KB", size / 1024);
    }
}