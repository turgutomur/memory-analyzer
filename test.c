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

   
    
    gets(buffer); 

    
    strcpy(buffer, "cok uzun bir metin kopyalaniyor"); 

    
    strcat(buffer, "ekleme yapiliyor");

    
    sprintf(buffer, "%s", user_input);

    -
    scanf("%s", buffer);



    timeinfo = gmtime(&rawtime);
    
    timeinfo = localtime(&rawtime);

    
    printf("Saat: %s", ctime(&rawtime));

   
    printf("Zaman: %s", asctime(timeinfo));


    
    printf(user_input); 

  
    fprintf(stdout, user_input);


    
    system("ls -la");

    
    FILE *fp = popen("ls", "r");
    pclose(fp);


  
    int count = 1000000;
    int size = 4096;
    
  
    void *ptr = malloc(count * size);
    free(ptr);

    return 0;
}