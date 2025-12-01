#ifndef MEMORY_ANALYZER_H
#define MEMORY_ANALYZER_H

#include "proc_parser.h"
#include "leak_detector.h"

#define MALLOC(size) tracked_malloc(size, __FILE__, __LINE__)
#define FREE(ptr) tracked_free(ptr, __FILE__, __LINE__)


#endif