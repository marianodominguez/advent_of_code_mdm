#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 255
#define MAX_CRATES 10

unsigned char crate[MAX_CRATES][MAX_CHAR];
unsigned char cline[MAX_CHAR];
int crates_done=0;
unsigned char ncrates=0;

unsigned char parse_crates(int n) {
    int i=1;
    int j=0;

    if (cline[1]=='1') {
        crates_done=1;
        return cline[n-3]-'0';
    }
    while(i<n) {
        if (cline[i]!='[' && cline[i]!=']' && cline[i]!='\n') {\
           printf("[%d] ", j);
           if (cline[i]!=' ') {
                strncat(crate[j], &cline[i],1);
                printf("=[%s] ", crate[j]);
           }
           j++;
           i=i+4;
           printf("\n");
        }
    }
    return j;
}

void perform_move() {
    int nmoves;
    char origin,dest;
    const char s[2]=" ";
    char *token;
    char *tmp ="";
    int ndest;
    int norig;
    token=strtok(cline,s); 
    if (strcmp(token, "move" ) !=0) return;
    nmoves=atoi(strtok(NULL,s));
    token=strtok(NULL,s); //from
    origin=atoi(strtok(NULL,s))-1;
    token=strtok(NULL,s); //to
    dest=atoi(strtok(NULL,s))-1;


    ndest=strlen(crate[dest]);
    norig=strlen(crate[origin]);
    if (nmoves>norig)
        nmoves=norig;
    if (norig>0) {
        strncat(crate[dest],&crate[origin][norig-nmoves],nmoves);
        crate[origin][norig-nmoves]='\0';
    }
    printf("move %d from %d to %d\n", nmoves, origin, dest );
    printf("[%s][%s][%s]\n", crate[0], crate[1],crate[2] );

}

void reverse(unsigned char*s) {
    char tmp;
    int i;
    int n=strlen(s);
    for(i=0; i<n/2;i++) {
        tmp=s[n-i-1];
        s[n-i-1]=s[i];
        s[i]=tmp;
    }
}

void read_data(void) {
    FILE* fd;
    int i=0;
    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while ( fgets(cline, MAX_CHAR, fd) != NULL && crates_done == 0) {
        ncrates=parse_crates(strlen(cline));
    }
    
    printf("Read %d crates\n", ncrates);
    for (i = 0; i < ncrates; i++) {
        reverse(crate[i]);
        //printf("[%s]\n" , crate[i]);
    }
    
    while (fgets(cline, MAX_CHAR, fd) != NULL) { 
        perform_move();
        i++;
    }

    fclose(fd);
}

int main(void)
{
    int i=0;

    read_data();
    printf("word: ");
    for(i=0;i<ncrates; i++) {
        int len=strlen(crate[i]);
        printf("%c",crate[i][len-1]);
    }
    
    cgetc();
    return 0;
}
