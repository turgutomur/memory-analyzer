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
        perror("Dosya acilamadi");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int line_num = 0;
    int issues_found = 0;

    while (fgets(line, sizeof(line), fp)) {
        line_num++;
        // Satır sonu karakterini temizle
        line[strcspn(line, "\n")] = 0;

        // 1. TEMEL TARAMA (-s ve -r modları için)
        for (int i = 0; i < NUM_FUNCTIONS; i++) {
            // Basit bir strstr araması yapıyoruz.
            // (Not: "mystrcpy" gibi isimleri de bulabilir, tam parser için lexer gerekir ama bu proje için strstr yeterli)
            char search_term[50];
            sprintf(search_term, "%s(", UNSAFE_FUNCTIONS[i]); // Fonksiyon çağrısı arıyoruz "gets("

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
            
            // 2.3.1 Format String Vulnerability
            // printf(user_input) gibi kullanımları arar (çift tırnak yoksa şüpheli)
            if (strstr(line, "printf(") && !strstr(line, "\"")) {
                printf("[CRITICAL] Line %d: Olası Format String Acigi (Tirnak isareti yok)\n", line_num);
                printf("  Code: %s\n", line);
            }

            // 2.3.2 Command Injection
            if (strstr(line, "system(")) {
                printf("[CRITICAL] Line %d: Command Injection Riski (system kullanilmis)\n", line_num);
            }

            // 2.3.3 Integer Overflow
            // malloc içinde çarpma işlemi (*) varsa şüpheli kabul ediyoruz 
            if (strstr(line, "malloc(") && strstr(line, "*")) {
                 printf("[WARNING] Line %d: Olası Integer Overflow (malloc icinde carpma islemi)\n", line_num);
                 printf("  Code: %s\n", line);
            }
        }
    }

    fclose(fp);

    if (mode == MODE_SCAN) {
        printf("Total %d security issues found.\n", issues_found); // 
    }
}