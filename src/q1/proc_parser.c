#include "proc_parser.h"
#include "utils.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUF_SIZE 1024

void parse_memory_maps() {
 
    
    FILE *fp;
    char line[LINE_BUF_SIZE];
    unsigned long seg_start[5] = {0}, seg_size[5] = {0};
    int found[5] = {0}; 

    fp = fopen("/proc/self/maps", "r");
    if (!fp) { perror("Dosya acilamadi"); return; }

    unsigned long start, end;
    char perms[5], offset[20], dev[10], inode[10], pathname[1024];
    int data_segment_found_flag = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;
        pathname[0] = '\0';
        sscanf(line, "%lx-%lx %s %s %s %s %s", &start, &end, perms, offset, dev, inode, pathname);
        unsigned long size = end - start;

        if (strstr(pathname, "[heap]")) { seg_start[2]=start; seg_size[2]=size; found[2]=1; }
        else if (strstr(pathname, "[stack]")) { seg_start[3]=start; seg_size[3]=size; found[3]=1; }
        else if (pathname[0] != '\0' && strstr(pathname, "/") && !strstr(pathname, ".so") && pathname[0] != '[') {
            if (strstr(perms, "x")) { seg_start[4]=start; seg_size[4]=size; found[4]=1; }
            else if (strstr(perms, "rw")) { seg_start[0]=start; seg_size[0]=size; found[0]=1; data_segment_found_flag=1; }
        }
        else if (data_segment_found_flag && pathname[0] == '\0' && strstr(perms, "rw")) {
            if (!found[1]) { seg_start[1]=start; seg_size[1]=size; found[1]=1; data_segment_found_flag=0; }
        }
    }
    
    printf("1.1 Memory Segment Analysis\n");
    const char *labels[] = {"Data segment", "BSS segment", "Heap segment", "Stack segment", "Text segment"};
    for (int i = 0; i < 5; i++) {
        if (found[i]) printf("%d. %-15s : start = 0x%lx, size = %lu Bytes\n", i + 1, labels[i], seg_start[i], seg_size[i]);
        else printf("%d. %-15s : (Not found/merged)\n", i + 1, labels[i]);
    }

    fseek(fp, 0, SEEK_SET);
    printf("\n1.2 List All Memory Segments\n1. Shared Libraries:\n");
    int lib_count = 2;
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;
        pathname[0] = '\0';
        sscanf(line, "%lx-%lx %s %s %s %s %s", &start, &end, perms, offset, dev, inode, pathname);
        unsigned long size = end - start;
        int is_lib = (strstr(pathname, ".so") != NULL);
        int is_vdso = (strstr(pathname, "[vdso]") != NULL);

        if (is_lib || is_vdso) {
            if (is_vdso) printf("\n4. Virtual Dynamic Shared Object (VDSO):\n");
            char size_str[32];
            format_size(size, size_str); // utils'den geliyor
            char *name = strrchr(pathname, '/');
            char *display_name = name ? name + 1 : pathname;
            printf("%d. %-15s : 0x%lx-0x%lx (%s) %s\n", (is_vdso ? 5 : lib_count++), display_name, start, end, size_str, perms);
        }
    }
    fclose(fp);
}

void parse_memory_status() {
    FILE *fp;
    char line[LINE_BUF_SIZE];
    long vm_size = 0, vm_rss = 0, vm_data = 0, vm_stk = 0, vm_exe = 0;
    fp = fopen("/proc/self/status", "r");
    if (!fp) { perror("Dosya acilamadi"); return; }
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strncmp(line, "VmSize:", 7) == 0) sscanf(line, "VmSize: %ld", &vm_size);
        else if (strncmp(line, "VmRSS:", 6) == 0) sscanf(line, "VmRSS: %ld", &vm_rss);
        else if (strncmp(line, "VmData:", 7) == 0) sscanf(line, "VmData: %ld", &vm_data);
        else if (strncmp(line, "VmStk:", 6) == 0) sscanf(line, "VmStk: %ld", &vm_stk);
        else if (strncmp(line, "VmExe:", 6) == 0) sscanf(line, "VmExe: %ld", &vm_exe);
    }
    fclose(fp);
    printf("\n1.3 Virtual vs Physical Memory Analysis\n");
    printf("1. Virtual Memory (VmSize)       : %ld KB\n", vm_size);
    printf("2. Physical Memory (VmRSS)       : %ld KB\n", vm_rss);
    printf("3. Data Segment (VmData)         : %ld KB\n", vm_data);
    printf("4. Stack Segment (VmStk)         : %ld KB\n", vm_stk);
    printf("5. Code Segment (VmExe)          : %ld KB\n", vm_exe);
    double efficiency = (vm_size > 0) ? ((double)vm_rss / vm_size) * 100.0 : 0.0;
    printf("6. Memory Efficiency             : %.2f%% (Physical/Virtual)\n", efficiency);
    printf("------------------------------------------------\n");
}