#include "code_parser.h"
#include <unistd.h> 

int check_file_exists(const char *filename) {
    
    if (access(filename, F_OK) != -1) {
        return 1; // Dosya var
    }
    return 0; // Dosya yok
}