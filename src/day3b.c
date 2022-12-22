#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 255
#define N_ITEMS 52
int n=0;
unsigned char line[MAX_CHAR];
unsigned char s[3][MAX_CHAR];


unsigned int sum_priorities=0;
int inventory[N_ITEMS];

unsigned int get_index(unsigned char x) {
    if (x>='a'&& x<='z') {
        return x-'a';
    }
    return x-'A'+26;
}


unsigned char get_duplicate(unsigned char *s1,unsigned char *s2,unsigned char *s3) {
    int i;
    int n = strlen(s1);
    unsigned char item;
    for(i=0; i<n; i++) {
        item=get_index(s1[i]);
        if(inventory[item]==-1) 
            inventory[item]=2;
        else
            inventory[item]=(2*inventory[item])%30;
    }
    n = strlen(s2);
    for(i=0; i<n; i++) {
        item=get_index(s2[i]);
        if(inventory[item]==-1) 
            inventory[item]=3;
        else
            inventory[item]=(3*inventory[item])%30;
    }
    n = strlen(s3);
    for(i=0; i<n; i++) {
        item=get_index(s3[i]);
        if(inventory[item]==-1) 
            inventory[item]=5;
        else
            inventory[item]=(5*inventory[item])%30;
    }

    for (i=0;i<N_ITEMS; i++) {
        //printf("%d, ", inventory[i]);
        if (inventory[i]==0)
            return i;
    }
    // No duplicate item
    return N_ITEMS+1;
}

void read_data(void) {
    unsigned int priority=0; 
    FILE* fd;
    unsigned char dup; 
    int i,j,k=0;
    for(i=0; i<=N_ITEMS; i++) {
        inventory[i]=-1;
    }
    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while ( fgets(line, MAX_CHAR, fd) != NULL ) {
        strcpy(s[k],line);
        k++;
        k=k%3;
        if (k==0) {
            dup=get_duplicate(s[0], s[1], s[2]);
            priority=dup+1;
            //printf("sacks: %s,%s,%s \n",s[]);
            printf("Duplicate: %d \n\n",dup);
            i++;
            sum_priorities=sum_priorities+priority;
            for(j=0; j<=N_ITEMS; j++) 
                inventory[j]=-1;
        }
    }
    printf("Read %d records\n", i);
    printf("Sum: %u \n", sum_priorities);
    fclose(fd);
}


int main(void)
{

    read_data();
    cgetc();
    return EXIT_SUCCESS;
}
