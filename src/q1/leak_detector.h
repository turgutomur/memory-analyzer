#ifndef LEAK_DETECTOR_H
#define LEAK_DETECTOR_H

#include <stddef.h>

void *tracked_malloc(size_t size, const char *file, int line);
void tracked_free(void *ptr, const char *file, int line);
void print_leak_report();

#endif