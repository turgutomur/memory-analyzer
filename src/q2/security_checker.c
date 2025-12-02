#include "security_checker.h"
#include "recommender.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

const char *UNSAFE_FUNCTIONS[] = {
    "strcpy", "strcat", "sprintf", "gets", "scanf",
    "gmtime", "localtime", "ctime", "asctime"
};
const int NUM_FUNCTIONS = 9;

void analyze_file(const char *filename, int mode) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int line_num = 0;
    int issues_found = 0;

    while (fgets(line, sizeof(line), fp)) {
        line_num++;
      
        line[strcspn(line, "\n")] = 0;

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

        if (mode == MODE_EXTENDED) {
            
            
            if ((strstr(line, "printf(") || strstr(line, "fprintf(")) && !strstr(line, "\"")) {
                printf("[CRITICAL] Line %d: Format String Vulnerability detected (no quotes used).\n", line_num);
                printf("  Code: %s\n", line);
                printf("  Hint: Use printf(\"%%s\", var) instead of printf(var).\n");
            }

            if (strstr(line, "system(") || strstr(line, "popen(")) {
                printf("[CRITICAL] Line %d: Command Injection Risk detected (system/popen used).\n", line_num);
                printf("  Code: %s\n", line);
                printf("  Hint: Avoid system()/popen(). Use fork() + execve() instead.\n");
            }

            if (strstr(line, "malloc(") && strstr(line, "*")) {
                 printf("[WARNING] Line %d: Potential Integer Overflow detected (multiplication in malloc).\n", line_num);
                 printf("  Code: %s\n", line);
                 printf("  Hint: Check for overflow before multiplication: if (count > SIZE_MAX / size) ...\n");
            }
        }
    }

    fclose(fp);

    if (mode == MODE_SCAN) {
        printf("Total %d security issues found.\n", issues_found);
    }
}