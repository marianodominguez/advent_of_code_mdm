#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 110
#define XMAX 99
#define YMAX 99

unsigned char line[MAX_CHAR];
unsigned char grid[YMAX][XMAX];

void fill_grid(unsigned char *line, unsigned char y) {
    unsigned int x;
    for(x=0; x<XMAX; x++) {
        grid[y][x]=line[x];
        //printf("g[%d][%d]=%c ",x,y,grid[x][y]);
    }
     //grid[y][XMAX]='\0';
    
    //printf("\n");
}

unsigned char visible_line(int x, int y) {
    int i;
    unsigned char visible_lane=4;
    for(i = x+1; i < XMAX; i++) {
        if (grid[y][x]<=grid[y][i]) {
            visible_lane--;
            i=XMAX;
        } 
    }
    for(i = x-1; i>=0; i--) { 
        if (grid[y][x]<=grid[y][i]){ 
            visible_lane--;
            i=-1;
        }
    }
    for(i = y+1; i < YMAX; i++) {
        if (grid[y][x]<=grid[i][x]) {
            visible_lane--;
            i=YMAX;
        }
    }
    for(i = y-1; i>=0; i--) {
        if (grid[y][x]<=grid[i][x]) {
            visible_lane--;
            i=-1;
        }
    }
    if (visible_lane == 0 ) return 0;
    return 1;
}

unsigned int find_visible() {
    unsigned char x,y, l=0;
    unsigned int v=0;
    for (y=1;y<YMAX-1;y++) {
        for (x=1;x<XMAX-1;x++) {
            l=visible_line(x,y);
            v=v+l;
            gotoxy(1,4);
        }
        printf("%d",y);
        //printf("\n");
    }
    return v;
}

int main(void)
{
    FILE *fd;
    unsigned int i=0;
    unsigned int visible=2*(XMAX+YMAX-2);

    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while(fgets(line, MAX_CHAR, fd)!=NULL) {
        fill_grid(line,i);
        gotoxy(1,3);
        printf(" %d ,[%c,%c]",i,line[0],line[XMAX-1]);
        //printf("-");
        i++;
    }
    fclose(fd);
    printf("\n");
    visible+=find_visible();
    printf("\nvisible trees= %d\n",visible);
    cgetc();
    return 0;
}
