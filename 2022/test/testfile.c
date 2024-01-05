#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 200

int main(void)
{
    int read;
    FILE* fd;
    char line[MAX_CHAR];
    
    fd=fopen("DATA.TXT","r");
    read = fgets(line, MAX_CHAR+1, fd);
    printf("Starting read\n");
    while ( read != EOF) {
        printf("line: %s\n",line );
        read = fgets(line, MAX_CHAR+1, fd);
    }
    
    fclose(fd);
    cgetc();
    return EXIT_SUCCESS;
}