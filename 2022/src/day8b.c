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

unsigned long tree_score(int x, int y) {
    int i;
    unsigned long p=0;
    unsigned long visible_lane[4]={0,0,0,0};
    if(x==0 || y==0 || x==XMAX || y==YMAX) return 0;

    for(i = x+1; i < XMAX; i++) {
        if (grid[y][i]<grid[y][x]) {
            visible_lane[0]++;
        } 
        else {
            visible_lane[0]++;
            i=XMAX;
        }
    }
    for(i = x-1; i>=0; i--) { 
        if (grid[y][i]<grid[y][x]){ 
            visible_lane[1]++;
        } 
        else {
            visible_lane[1]++;
            i=-1;
        }
    }
    for(i = y+1; i < YMAX; i++) {
        if (grid[i][x]<grid[y][x]) {
            visible_lane[2]++;            
        }
        else {
            visible_lane[2]++;
            i=YMAX;
        }
    }
    for(i = y-1; i>=0; i--) {
        if (grid[i][x]<grid[y][x]) {
            visible_lane[3]++;
        }
        else {
            visible_lane[3]++;
            i=-1;
        }
    }
    p=visible_lane[0]*visible_lane[1]*visible_lane[2]*visible_lane[3];
    //printf("[%d,%d,%d,%d]=%lu\n",visible_lane[0],visible_lane[1],visible_lane[2],visible_lane[3],p);
    return p;
}

unsigned int find_visible() {
    unsigned char x,y;
    unsigned long l,v=0;
    for (y=1;y<YMAX-1;y++) {
        for (x=1;x<XMAX-1;x++) {
            l=tree_score(x,y);
            if (l>v) v=l;
            //gotoxy(1,4);
            //printf("[%d,%d]=(%c)%d ",x,y,grid[y][x],l);
        }
        printf("%d ,%lu ",y,v);
        printf("\n");
    }
    return v;
}

int main(void)
{
    FILE *fd;
    unsigned int i=0;
    unsigned long visible=0;

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
    visible=find_visible();
    printf("\nmax score= %lu \n",visible);
    cgetc();
    return 0;
}
