#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char buffer[10];
    
    // --- 1. Güvensiz Fonksiyonlar (Scan & Recommend Modu) ---
    gets(buffer);  
    strcpy(buffer, "a very long piece of data"); 
    
    // --- 2. Genişletilmiş Analiz (Extended Modu) ---
    char *user_input = "dangerous_input";
    printf(user_input); 
    
    system("ls -la"); 
    
    return 0;
}