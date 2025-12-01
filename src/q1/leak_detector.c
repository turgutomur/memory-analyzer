#include "leak_detector.h"
#include <stdio.h>
#include <stdlib.h>

struct AllocationRecord {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    struct AllocationRecord *next;
};

static struct AllocationRecord *alloc_head = NULL;
static int total_allocations = 0;
static int total_freed = 0;
static int leaked_blocks = 0;

void *tracked_malloc(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    if (!ptr) return NULL;
    struct AllocationRecord *new_node = (struct AllocationRecord *)malloc(sizeof(struct AllocationRecord));
    if (new_node) {
        new_node->ptr = ptr;
        new_node->size = size;
        new_node->file = file;
        new_node->line = line;
        new_node->next = alloc_head;
        alloc_head = new_node;
        total_allocations++;
    }
    return ptr;
}

void tracked_free(void *ptr, const char *file, int line) {
    if (!ptr) return;
    struct AllocationRecord *curr = alloc_head, *prev = NULL;
    while (curr) {
        if (curr->ptr == ptr) {
            if (prev) prev->next = curr->next; else alloc_head = curr->next;
            free(curr); free(ptr); total_freed++; return;
        }
        prev = curr; curr = curr->next;
    }
    printf("UYARI: Gecersiz free denemesi! (%s:%d)\n", file, line);
}

void print_leak_report() {
    printf("\n=== 1.4 Memory Leak Report ===\n");
    struct AllocationRecord *curr = alloc_head;
    leaked_blocks = 0;
    while (curr) { leaked_blocks++; curr = curr->next; }
    printf("Total Allocations: %d\n", total_allocations);
    printf("Total Freed      : %d\n", total_freed);
    printf("Leaked Blocks    : %d\n", leaked_blocks);
    if (leaked_blocks > 0) {
        printf("\n--- Detayli Sizinti Raporu ---\n");
        curr = alloc_head;
        int id = 1;
        while (curr) {
            printf("Block #%d: %zu bytes at %p\n", id++, curr->size, curr->ptr);
            printf("  Allocated at: %s:%d\n", curr->file, curr->line);
            curr = curr->next;
        }
    }
    printf("==============================\n");
}