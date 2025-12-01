#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char buffer[10];
    
    // Test: Gets (Unsafe)
    gets(buffer); 
    
    // Test: Strcpy (Unsafe)
    strcpy(buffer, "cok uzun bir veri"); 
    
    // Test: System (Command Injection)
    system("ls");

    // Test: Format String
    char *input = "risk";
    printf(input);
    
    return 0;
}