#include "security_checker.h"
#include "recommender.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Taranacak güvensiz fonksiyonlar listesi 
const char *UNSAFE_FUNCTIONS[] = {
    "strcpy", "strcat", "sprintf", "gets", "scanf",
    "gmtime", "localtime", "ctime", "asctime"
};
const int NUM_FUNCTIONS = 9;

void analyze_file(const char *filename, int mode) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int line_num = 0;
    int issues_found = 0;

    while (fgets(line, sizeof(line), fp)) {
        line_num++;
        
        line[strcspn(line, "\n")] = 0;

        // 1. TEMEL TARAMA (-s ve -r modları için)
        for (int i = 0; i < NUM_FUNCTIONS; i++) {
            
            char search_term[50];
            sprintf(search_term, "%s(", UNSAFE_FUNCTIONS[i]); 

            if (strstr(line, search_term)) {
                issues_found++;
                
                if (mode == MODE_SCAN) {
                    
                    printf("Line %d: %s() used\n", line_num, UNSAFE_FUNCTIONS[i]);
                }
                else if (mode == MODE_RECOMMEND) {
                    
                    printf("Line %d: %s() used", line_num, UNSAFE_FUNCTIONS[i]);
                    print_recommendation(UNSAFE_FUNCTIONS[i]);
                }
            }
        }

        // 2. GENİŞLETİLMİŞ ANALİZ (-x modu) 
        if (mode == MODE_EXTENDED) {
            
           
            if (strstr(line, "printf(") && !strstr(line, "\"")) {
                printf("[CRITICAL] Line %d: Possible Format String Vulnerability (missing quotation marks)\n", line_num);
                printf("  Code: %s\n", line);
            }

       
            if (strstr(line, "system(")) {
                printf("[CRITICAL] Line %d: Command injection risk (system used)\n", line_num);
            }

            
            if (strstr(line, "malloc(") && strstr(line, "*")) {
                 printf("[WARNING] Line %d: Possible Integer Overflow (multiplication inside malloc)\n", line_num);
                 printf("  Code: %s\n", line);
            }
        }
    }

    fclose(fp);

    if (mode == MODE_SCAN) {
        printf("Total %d security issues found.\n", issues_found); // 
    }
}