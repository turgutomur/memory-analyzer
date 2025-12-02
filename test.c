#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char buffer[50];
    char *user_input = "tehlikeli_girdi";
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);

    // ==========================================
    // 1. TEMEL GÜVENSİZ FONKSİYONLAR (Scan/Recommend)
    // ==========================================
    
    // [HATA] Buffer Overflow Riski
    gets(buffer); 

    // [HATA] Hedef boyut kontrolü yok
    strcpy(buffer, "cok uzun bir metin kopyalaniyor"); 

    // [HATA] Hedef boyut kontrolü yok
    strcat(buffer, "ekleme yapiliyor");

    // [HATA] Formatlama taşması riski
    sprintf(buffer, "%s", user_input);

    // [HATA] Sınırsız okuma riski
    scanf("%s", buffer);


    // ==========================================
    // 2. ZAMAN FONKSİYONLARI (Thread-Safety Riski)
    // ==========================================
    
    // [HATA] Thread-safe değil (Statik buffer kullanır)
    timeinfo = gmtime(&rawtime);
    
    // [HATA] Thread-safe değil
    timeinfo = localtime(&rawtime);

    // [HATA] Buffer boyutu kontrol edilemez
    printf("Saat: %s", ctime(&rawtime));

    // [HATA] Thread-safe değil
    printf("Zaman: %s", asctime(timeinfo));


    // ==========================================
    // 3. GENİŞLETİLMİŞ ANALİZ (-x Mode)
    // ==========================================

    // --- 3.1 Format String Açıkları ---
    // [HATA] printf içinde format belirteci yok (User input direkt veriliyor)
    printf(user_input); 

    // [HATA] fprintf içinde format belirteci yok
    fprintf(stdout, user_input);


    // --- 3.2 Command Injection ---
    // [HATA] System fonksiyonu tehlikeli
    system("ls -la");

    // [HATA] Popen fonksiyonu tehlikeli
    FILE *fp = popen("ls", "r");
    pclose(fp);


    // --- 3.3 Integer Overflow ---
    int count = 1000000;
    int size = 4096;
    
    // [HATA] Malloc içinde çarpma işlemi (Overflow kontrolü yok)
    void *ptr = malloc(count * size);
    free(ptr);

    return 0;
}