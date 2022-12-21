#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 3
#define MAX_LINES 2510

unsigned char guide[MAX_LINES][2];
unsigned int guide_len=0;

void read_data(void) {
    char* read;
    FILE* fd;
    char line[MAX_CHAR+1];
    int i=0;
    read = "";
    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while ( read != NULL ) {
        read = fgets(line, MAX_CHAR+1, fd);
        read[MAX_CHAR]='\0';
        if (strcmp(read,"")!=0 && strcmp(read,"\n")!=0) {
            guide[i][0]=read[0];
            guide[i][1]=read[2];
            i++;
        }
    }
    guide_len=i;
    printf("Read %d records\n", i);    
    fclose(fd);
}

unsigned int play(char b, char r) {
    char a;
    switch (r)
    {
    case 0:
        if (b==0) a=2;
        if (b==1) a=0;
        if (b==2) a=1;
        break;
    case 2:
        if (b==0) a=1;
        if (b==1) a=2;
        if (b==2) a=0;
        break;
    default:
        a=b;
        break;
    }
    //printf("%d ",a);
    if(a==b) return 3+a+1;
    if ( (a==0 && b==2) || (a==1 && b==0) || (a==2 && b==1) ) return 6+a+1;
    return a+1;
}

int main(void)
{
    unsigned int i=0;
    unsigned int pscore=0;
    unsigned long score=0;
    unsigned char opponent,result;
    read_data();
    for(i=0;i<guide_len;i++) {
        opponent    =   guide[i][0]-'A';
        result      =   guide[i][1]-'X';
        pscore=play(opponent,result);
        score=score + pscore;
        //printf("%c,%c = %d \n", guide[i][0],guide[i][1], pscore); 
    }
    printf("Score: %lu\n", score);
    cgetc();
    return EXIT_SUCCESS;
}
