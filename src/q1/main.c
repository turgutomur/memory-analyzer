#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "memory_analyzer.h" 

void perform_leak_test() {
    printf("--- Leak Check Test Senaryosu ---\n");
    char *p1 = MALLOC(100);
    char *p2 = MALLOC(200);
    FREE(p1);
    print_leak_report();
    // free(p2);
}

void print_usage() {
    printf("Kullanim: ./app1 [args]\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("--- Basic Analysis ---\n");
        parse_memory_maps(); 
    } 
    else if (argc == 2) {
        if (strcmp(argv[1], "-leak-check") == 0) {
            perform_leak_test();
        } 
        else if (strcmp(argv[1], "--all") == 0) {
            parse_memory_maps();   
            parse_memory_status();
            print_leak_report();
        } 
        else print_usage();
    }
    else if (argc == 3 && strcmp(argv[1], "-monitor") == 0) {
        int sec = atoi(argv[2]);
        while(1) {
            parse_memory_status(); 
            sleep(sec);
            printf("------------------------\n");
        }
    }
    else print_usage();
    return 0;
}