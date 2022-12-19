#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 200

int main(void)
{
    unsigned long sum=0;
    char* read;
    FILE* fd;
    unsigned long maxcalories=0;
    int elf=0;
    char line[MAX_CHAR];
    
    fd=fopen("DATA.TXT","r");
    read = "";

    printf("Starting max calories count\n");
    while ( read != NULL) {
        read = fgets(line, MAX_CHAR+1, fd);
        if (strcmp(read,"\n")==0 || read==NULL) {
            if (maxcalories<sum) 
                maxcalories=sum;
            elf++;
            printf("elf %d, calories %lu\n",elf,sum);
            sum=0;
        } else {
            sum=sum+atol(read);
        }
    }
    
    printf("\n last elf: %d, Max calories= %lu" , elf, maxcalories);
    cgetc();
    fclose(fd);
    return EXIT_SUCCESS;
}
