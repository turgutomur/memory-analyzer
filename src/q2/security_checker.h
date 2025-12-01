#ifndef SECURITY_CHECKER_H
#define SECURITY_CHECKER_H

// Modlar
#define MODE_SCAN 1          // -s
#define MODE_RECOMMEND 2     // -r
#define MODE_EXTENDED 3      // -x

// Verilen dosyayı belirtilen modda analiz et
void analyze_file(const char *filename, int mode);

#endif