#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 10

FILE *fd;
unsigned char line[MAX_CHAR];
unsigned char screen[40][6];


void parse_command(unsigned char *line) {
    unsigned char *cmd;
    int val;
    if (strncmp(line,"noop",4)==0) {
        clock();
    }
    else {
        clock();
        sscanf(line, "%s %d", cmd, &val);
        clock();
        xreg+=val;
        //printf("%s[%d]\n", cmd, val);
    }
    return;
}

int main(void)
{
    int x,y;

    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while(fgets(line, MAX_CHAR, fd)!=NULL) {
        parse_command(line);
    }
    fclose(fd);

    cgetc();
    return 0;
}
