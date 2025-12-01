#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char buffer[10];
    
    // --- 1. Güvensiz Fonksiyonlar (Scan & Recommend Modu) ---
    gets(buffer);  // [HATA] Buffer overflow riski
    strcpy(buffer, "cok uzun bir yazi"); // [HATA] Hedef boyut kontrolü yok
    
    // --- 2. Genişletilmiş Analiz (Extended Modu) ---
    char *user_input = "tehlikeli";
    printf(user_input); // [HATA] Format string açığı
    
    system("ls -la"); // [HATA] Command injection riski
    
    return 0;
}