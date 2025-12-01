#include <stdio.h>
#include <string.h>
#include "security_checker.h"
#include "code_parser.h"

// Yardım Menüsü
void print_usage() {
    printf("Kullanim:\n");
    printf("  ./app2 -s <file1> [file2] ...  : Tarama Modu\n");
    printf("  ./app2 -r <file1> [file2] ...  : Oneri Modu\n");
    printf("  ./app2 -x <file1> [file2] ...  : Genisletilmis Analiz\n");
}

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        print_usage();
        return 1;
    }

    const char *mode_arg = argv[1];
    int mode = 0;

    
    if (strcmp(mode_arg, "-s") == 0) {
        mode = MODE_SCAN;
    } 
    else if (strcmp(mode_arg, "-r") == 0) {
        mode = MODE_RECOMMEND;
    }
    else if (strcmp(mode_arg, "-x") == 0) {
        mode = MODE_EXTENDED;
    }
    else {
        printf("Hata: Gecersiz mod '%s'\n", mode_arg);
        print_usage();
        return 1;
    }


    
    for (int i = 2; i < argc; i++) {
        const char *filename = argv[i];

        
        printf("\n========================================\n");
        printf(" FILE: %s\n", filename);
        printf("========================================\n");

        if (check_file_exists(filename)) {
            analyze_file(filename, mode);
        } else {
            printf("Hata: '%s' dosyasi bulunamadi.\n", filename);
        }
    }

    return 0;
}