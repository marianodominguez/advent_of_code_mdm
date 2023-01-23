#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 10

FILE *fd;
unsigned char line[MAX_CHAR];
int cycle=1,signal_strength=0;
int xreg=1;

void clock() {
    if (cycle%40==20) {
        signal_strength+=cycle*xreg;
        printf("%d[%d]= %d\n", cycle, xreg, cycle*xreg);
    }
    cycle++;

}

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

    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while(fgets(line, MAX_CHAR, fd)!=NULL) {
        parse_command(line);
    }
    fclose(fd);
    printf("sum : %d \n", signal_strength);
    cgetc();
    return 0;
}
