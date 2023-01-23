#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 10

FILE *fd;
unsigned char line[MAX_CHAR];
unsigned char screen[40][6];
int cycle=1,signal_strength=0;
int xreg=1;
int xp=0,yp=0;

void clock() {
    xp=(cycle-1)%40;
    yp=(int)(cycle/40);
    if (abs(xreg-xp)<=1) screen[xp][yp]=1;

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
    int x,y;

    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while(fgets(line, MAX_CHAR, fd)!=NULL) {
        parse_command(line);
    }
    fclose(fd);

    for (x=0;x<40;x++) {
        for (y=0;y<6;y++)
        if (screen[x][y]==1) {
            cputsxy(x,y,"#");
        }
        else {
             cputsxy(x,y,".");
        }
    }
    cgetc();
    return 0;
}
