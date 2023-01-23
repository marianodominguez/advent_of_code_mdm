#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_X 500
#define MAX_Y 500
// Unable to fit this in 65 Kb., solution in py 
#define MAXSIZE 10000

unsigned long visitedht[MAXSIZE];
unsigned int hx=MAX_X/2+70,hy=MAX_Y/2+40;
unsigned int tx,ty;
unsigned int xmin=MAX_X,xmax=0,ymin=MAX_Y,ymax=0;
unsigned char buffer[10];
unsigned int nvisited,visited=0;

unsigned long hashcode(unsigned int x, unsigned int y) {
    return (y*MAX_X+x);
}

int max(int a, int b) {
    if(a>b) return a;
    return b;
}

int min(int a, int b) {
    if(a<b) return a;
    return b;
}


void print_grid(void) {
    gotoxy(20,0);
    printf("%d %d ", tx,ty);
    gotoxy(20,1);
    printf("%d %d ", hx,hy);
    gotoxy(20,9);
    printf("min=(%d,%d) ",xmin,ymin);
    gotoxy(20,10);    
    printf("max=(%d,%d) ",xmax,ymax);
    /*
    if (hx<5 || hx+5>=MAX_X || hy<5 || hy+5>=MAX_Y) return;

    for(x=hx-5;x<hx+5;x++){
        for(y=hy-5;y<hy+5; y++) {        
            gotoxy(x-hx+5,y-hy+5);
            printf(".");
            gotoxy(x-hx+5,y-hy+5);
            if (x==hx && y==hy) printf("H");
            gotoxy(x-hx+5,y-hy+5);
            if (x==tx && y==ty) printf("T");
        }
    }
    */
}

void count_positions(int x, int y) {
    int i=0;
    for(i=0; i<nvisited;i++) {
        if (visitedht[i]=hashcode(x,y))
            return;
    }
    visitedht[nvisited]=hashcode(x,y);
    nvisited++;

}

void move_tail(unsigned char dir) {
    int dx,dy=0;
    dx=hx;
    dx-=tx;
    dy=hy;
    dy-=ty;
    gotoxy(20,3);
    printf("[%d][%d]  ",dx,dy);
    if ( abs(dx)<=1 && abs(dy)<=1) return;
    if(abs(dx)>=2 && abs(dy)>0) {
        tx+=dx/abs(dx);
        ty+=dy/abs(dy);
        dir='X';
    }
    if(abs(dy)>=2 && abs(dx)>0) {
        tx+=dx/abs(dx);
        ty+=dy/abs(dy);
        dir='X';        
    }
    if(dir=='L') {
        tx--;
    }  
    if(dir=='R') {
        tx++;
    } 
    if(dir=='D') { 
        ty++;
    }
    if(dir=='U') {
        ty--;
    }

    xmax=max(hx, xmax);
    ymax=max(hy, ymax);
    xmin=min(hx, xmin);
    ymin=min(hy, ymin);

    if(tx-1>=MAX_X || hx-1 >= MAX_X || ty-1 >= MAX_Y || hy-1 >= MAX_Y) {
        gotoxy(0,11);
        printf("Out of bounds! h[%d,%d],t[%d,%d]",hx,hy,tx,ty);
        cgetc();
        exit(1);
    }
    count_positions(tx,ty);
}

void move_head(unsigned char dir,unsigned int size) {
    int dx=0;
    int dy=0;
    unsigned char i;
    
    gotoxy(20,2);
    printf("%c %d", dir,size);
    if(dir=='D') dy=1;
    if(dir=='U') dy=-1;
    if(dir=='R') dx=1;
    if(dir=='L') dx=-1;

    for(i=0; i<size; i++) {            
        hx+=dx;
        hy+=dy;
        move_tail(dir);
        print_grid();
    }
}



int main(void)
{
    FILE *fd;
    unsigned char size[4];
    unsigned char dir;
    int i=0;
    tx=hx;
    ty=hy;
 
    //visitedht[hashcode(tx,ty)]=1;

    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while (fgets(buffer, 7, fd)!=NULL)
    {
        strncpy(size, &buffer[1],4);
        i++;
        dir=buffer[0];
        move_head(dir,atoi(size));
        gotoxy(20,4);
        printf("i=%d    ",i);
        gotoxy(20,7);
        printf("n: %d   ", nvisited);
    }

    fclose(fd);
    cgetc();
    
    return EXIT_SUCCESS;
}
