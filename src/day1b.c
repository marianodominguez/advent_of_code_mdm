#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 200


void record_calories(unsigned long a[], long x) {
    if (x<=a[2]) return;
    if (x>a[0]) {
        a[1]=a[0];
        a[2]=a[1];
        a[0]=x;
        return;
    } 
    if (x>a[1]) {
        a[2] = a[1];
        a[1]=x;
        return;
    }
    a[2]=x;
    return;
}

int main(void)
{
    unsigned long top_three[]= {0,0,0};
    unsigned long sum=0;
    char* read;
    FILE* fd;
    int elf=0;
    int i;
    char line[MAX_CHAR];
    
    fd=fopen("DATA.TXT","r");
    read = "";

    printf("Starting max calories count\n");
    while ( read != NULL) {
        read = fgets(line, MAX_CHAR+1, fd);
        if (strcmp(read,"\n")==0 || read==NULL) {
            
            record_calories(top_three, sum);

            elf++;
            printf("elf %d, calories %lu\n",elf,sum);
            sum=0;
        } else {
            sum=sum+atol(read);
        }
    }
    for(i=0;i<3;i++) {
        printf("%lu ",top_three[i] );
        sum=sum+top_three[i];
    }

    printf("last elf: %d, Max calories= %lu" , elf, sum);
    cgetc();
    fclose(fd);
    return EXIT_SUCCESS;
}
