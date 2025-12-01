#include "recommender.h"
#include <stdio.h>
#include <string.h>

void print_recommendation(const char *func_name) {
    printf("\n--- Recommendation: %s ---\n", func_name);

    // 1. gets [cite: 108]
    if (strcmp(func_name, "gets") == 0) {
        printf("Issue: gets() does not check the length of the input, which can easily cause buffer overflows.\n");
        printf("       It can lead to crashes, data corruption, or serious security vulnerabilities.\n");
        printf("Suggestion: Use fgets() instead of gets().\n");
        printf("Example:\n  // Unsafe: gets(buffer);\n  // Safe:   fgets(buffer, sizeof(buffer), stdin);\n");
    }
    // 2. strcpy [cite: 105]
    else if (strcmp(func_name, "strcpy") == 0) {
        printf("Issue: strcpy() does not check the destination buffer size. If source is longer than dest,\n");
        printf("       it will cause a buffer overflow.\n");
        printf("Suggestion: Use strncpy() instead of strcpy().\n");
        printf("Example:\n  // Safe: strncpy(dest, src, sizeof(dest)-1); dest[sizeof(dest)-1] = '\\0';\n");
    }
    // 3. strcat [cite: 106]
    else if (strcmp(func_name, "strcat") == 0) {
        printf("Issue: strcat() does not check if the destination buffer has enough space for the appended string.\n");
        printf("Suggestion: Use strncat() instead of strcat().\n");
    }
    // 4. sprintf [cite: 107]
    else if (strcmp(func_name, "sprintf") == 0) {
        printf("Issue: sprintf() writes to a buffer without bounds checking, leading to potential overflows.\n");
        printf("Suggestion: Use snprintf() instead of sprintf().\n");
        printf("Example:\n  // Safe: snprintf(buf, sizeof(buf), \"%%s\", src);\n");
    }
    // 5. scanf [cite: 109]
    else if (strcmp(func_name, "scanf") == 0) {
        printf("Issue: scanf() with %%s can write past the end of the buffer if input is too long.\n");
        printf("Suggestion: Use width specifiers (e.g., %%99s) to limit input size.\n");
    }
    // 6. gmtime [cite: 111]
    else if (strcmp(func_name, "gmtime") == 0) {
        printf("Issue: gmtime() returns a pointer to static data and is not thread-safe.\n");
        printf("Suggestion: Use gmtime_r() for a thread-safe alternative.\n");
    }
    // 7. localtime [cite: 112]
    else if (strcmp(func_name, "localtime") == 0) {
        printf("Issue: localtime() returns a pointer to static data and is not thread-safe (race condition risk).\n");
        printf("Suggestion: Use localtime_r() for a thread-safe alternative.\n");
    }
    // 8. ctime [cite: 113]
    else if (strcmp(func_name, "ctime") == 0) {
        printf("Issue: ctime() is not thread-safe and does not allow buffer size control.\n");
        printf("Suggestion: Use ctime_r() for a thread-safe alternative.\n");
    }
    // 9. asctime [cite: 114]
    else if (strcmp(func_name, "asctime") == 0) {
        printf("Issue: asctime() is not thread-safe.\n");
        printf("Suggestion: Use asctime_r() or strftime() for safer time formatting.\n");
    }
    // Ekstra: system (Extended check context)
    else if (strcmp(func_name, "system") == 0) {
        printf("Issue: Using system() poses a Command Injection risk if input is not sanitized.\n");
        printf("Suggestion: Use execve() family functions instead.\n");
    }
    else {
        printf("General security warning: Ensure proper bounds checking and input validation for this function.\n");
    }
    printf("-------------------------\n");
}