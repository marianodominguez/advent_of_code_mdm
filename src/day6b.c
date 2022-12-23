#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 26
#define PKG_LEN 14
unsigned char buffer[PKG_LEN];
unsigned int inv[MAX_CHAR];

int nonrepeat(unsigned char* s) {
    int i;
    printf("[%s]\n",s);
    for(i=0; i<PKG_LEN;i++) {
        
        inv[s[i]-'a']=0;
    }
    for(i=0; i<PKG_LEN;i++) {
        inv[s[i]-'a']=inv[s[i]-'a']+1;
    }
    for(i=0; i<PKG_LEN;i++) {
        if (inv[s[i]-'a']>1) return 0;
    }
    return 1;   
}

int read_data(void) {
    FILE* fd;
    int i,n=0;
    int byte=0;
    unsigned char b;
    unsigned char* tmp;
    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
   
    while (byte!=EOF) {
        byte=fscanf(fd,"");
        b=byte;
        //printf("\n%c,",byte);
        if(i<PKG_LEN) {
            strncat(buffer,&b,1);
            i++;
        } else {
            if(nonrepeat(buffer)==1) 
                return n;
            strcpy(tmp,"");
            strncat(tmp,&buffer[1],PKG_LEN-1);
            strncat(tmp,&b,1);
            strcpy(buffer,tmp);    
        }
        n++;
    }
    fclose(fd);
    return -1;
}

int main(void)
{
    int i=0;
    i=read_data();
    printf("N=%d",i);
    cgetc();
    return 0;
}