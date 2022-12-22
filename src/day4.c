#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 255
#define N_ITEMS 52
int n=0;
unsigned char line[MAX_CHAR];
unsigned char elf[2][MAX_CHAR];


char is_duplicate(s1,s2) {
    char *token;
    unsigned int r1[2];
    unsigned int r2[2];

    token=strtok(s1,"-");
    r1[0]=atoi(token);
    token=strtok(NULL,"-");
    r1[1]=atoi(token);

    token=strtok(s2,"-");
    r2[0]=atoi(token);
    token=strtok(NULL,"-");
    r2[1]=atoi(token);

    printf("%d,%d - %d,%d\n", r1[0],r1[1],r2[0],r2[1]);

    if ( r1[0]<=r2[0] && r1[1]>=r2[1]) 
        return 1;
    if ( r2[0] <= r1[0] && r2[1]>=r1[1]) 
        return 1;
    
    return 0;
}


void read_data(void) {
    unsigned int priority=0; 
    FILE* fd;
    int i,count=0;
    char *token;
    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while ( fgets(line, MAX_CHAR, fd) != NULL ) {
        token=strtok(line, ",");
        strcpy(elf[0], token);
        token=strtok(NULL, ",");
        strcpy(elf[1], token);
        if (is_duplicate(elf[0],elf[1])) {
            count ++;
        }
        i++;
    }
    printf("Read %d records\n", i);
     printf("found %d duplicates\n", count);

    fclose(fd);
}


int main(void)
{

    read_data();
    cgetc();
    return EXIT_SUCCESS;
}
