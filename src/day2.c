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
    int j,i=0;
    read = "";
    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while ( read != NULL ) {
        read = fgets(line, MAX_CHAR+1, fd);
        read[MAX_CHAR]='\0';
        if (strcmp(read,"")!=0 && strcmp(read,"\n")!=0) {
            guide[i][0]=read[0];
            guide[i][1]=read[2];
            //printf("%c%c\n", guide[i][0],guide[i][1]);
            i++;
        }
    }
    guide_len=i;
    printf("Read %d records\n", i);    
    fclose(fd);
}

unsigned int play(char a, char b) {
    if(a==b) return 3;
    if ( (a==0 && b==2) || (a==1 && b==0) || (a==2 && b==1) ) return 6;
    return 0;
}

int main(void)
{
    unsigned int i=0;
    unsigned int pscore=0;
    unsigned long score=0;
    unsigned char opponent,myplay;
    read_data();
    for(i=0;i<guide_len;i++) {
        opponent    =   guide[i][0]-'A';
        myplay      =   guide[i][1]-'X';
        pscore=play(myplay,opponent) ;
        //printf("calculating play: %d,%d= %c%c =%d + %d \n", selected, counter, guide[i][0], guide[i][1], pscore, myplay+1);        
        score=score + pscore + myplay+1;
    }
    printf("Score: %lu\n", score);
    cgetc();
    return EXIT_SUCCESS;
}
