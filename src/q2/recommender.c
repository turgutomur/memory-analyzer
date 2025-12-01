#include "recommender.h"
#include <stdio.h>
#include <string.h>

void print_recommendation(const char *func_name) {
    printf("\n--- Oneri: %s ---\n", func_name);

    if (strcmp(func_name, "gets") == 0) {
        printf("Sorun: gets() girdi uzunlugunu kontrol etmez, buffer overflow'a neden olur.\n");
        printf("Cozum: fgets() kullanin.\n");
        printf("Ornek:\n  // Unsafe: gets(buf);\n  // Safe:   fgets(buf, sizeof(buf), stdin);\n");
    }
    else if (strcmp(func_name, "strcpy") == 0) {
        printf("Sorun: strcpy() hedef buffer boyutunu kontrol etmez.\n");
        printf("Cozum: strncpy() kullanin.\n");
        printf("Ornek:\n  // Safe: strncpy(dest, src, sizeof(dest)-1); dest[sizeof(dest)-1] = '\\0';\n");
    }
    else if (strcmp(func_name, "strcat") == 0) {
        printf("Sorun: strcat() hedef buffer'in tasip tasmayacagini kontrol etmez.\n");
        printf("Cozum: strncat() kullanin.\n");
    }
    else if (strcmp(func_name, "sprintf") == 0) {
        printf("Sorun: sprintf() tasma riski tasir.\n");
        printf("Cozum: snprintf() kullanin.\n");
    }
    else if (strcmp(func_name, "scanf") == 0) {
        printf("Sorun: scanf() string okurken boyut sinirlamasi yapmazsa tasma olur.\n");
        printf("Cozum: Genislik belirteci kullanin (orn: %%99s).\n");
    }
    else if (strcmp(func_name, "system") == 0) {
        printf("Sorun: Command Injection riski.\n");
        printf("Cozum: execve() ailesi fonksiyonlari kullanin.\n");
    }
    else {
        printf("Bu fonksiyon icin genel guvenlik kontrolleri yapin.\n");
    }
    printf("-------------------------\n");
}