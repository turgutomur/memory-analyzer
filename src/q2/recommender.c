#include "recommender.h"
#include <stdio.h>
#include <string.h>

void print_recommendation(const char *func_name) {
    printf("\n--- Recommendation: %s ---\n", func_name);

    if (strcmp(func_name, "gets") == 0) {
        printf("Issue: gets() does not check input length and can cause buffer overflow.\n");
        printf("Solution: Use fgets().\n");
        printf("Example:\n  // Unsafe: gets(buf);\n  // Safe:   fgets(buf, sizeof(buf), stdin);\n");
    }
    else if (strcmp(func_name, "strcpy") == 0) {
        printf("Issue: strcpy() does not check the size of the destination buffer.\n");
        printf("Solution: Use strncpy().\n");
        printf("Example:\n  // Safe: strncpy(dest, src, sizeof(dest)-1); dest[sizeof(dest)-1] = '\\0';\n");
    }
    else if (strcmp(func_name, "strcat") == 0) {
        printf("Issue: strcat() does not ensure the destination buffer will not overflow.\n");
        printf("Solution: Use strncat().\n");
    }
    else if (strcmp(func_name, "sprintf") == 0) {
        printf("Issue: sprintf() is prone to overflow.\n");
        printf("Solution: Use snprintf().\n");
    }
    else if (strcmp(func_name, "scanf") == 0) {
        printf("Issue: scanf() can overflow when reading strings if no size limit is provided.\n");
        printf("Solution: Use a width specifier (e.g., %%99s).\n");
    }
    else if (strcmp(func_name, "system") == 0) {
        printf("Issue: Risk of command injection.\n");
        printf("Solution: Use the execve() family of functions.\n");
    }
    else {
        printf("Perform general security checks for this function.\n");
    }
    printf("-------------------------\n");
}