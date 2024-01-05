#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHAR 255
#define N_ITEMS 52
int n=0;
unsigned char line[MAX_CHAR];
unsigned int sum_priorities=0;
int inventory[N_ITEMS];

unsigned int get_index(unsigned char x) {
    if (x>='a'&& x<='z') {
        return x-'a';
    }
    return x-'A'+26;
}


unsigned char get_duplicate(unsigned char *line) {
    int i;
    int n = strlen(line);
    unsigned char item;
    for(i=0; i<n/2; i++) {
        item=get_index(line[i]);
        if(inventory[item]==-1) 
            inventory[item]=2;

        else
            inventory[item]=(2*inventory[item])%6;
    }
    for(i=n/2; i<n; i++) {
        item=get_index(line[i]);
        if(inventory[item]==-1) 
            inventory[item]=3;
        else
            inventory[item]=(3*inventory[item])%6;
    }

    for (i=0;i<N_ITEMS; i++) {
        //printf("%d, ", inventory[i]);
        if (inventory[i]%6==0)
            return i;
    }
    // No duplicate item
    return N_ITEMS+1;
}

void read_data(void) {
    unsigned int priority=0; 
    FILE* fd;
    unsigned char dup; 
    int i,j=0;
    for(i=0; i<=N_ITEMS; i++) {
        inventory[i]=-1;
    }
    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while ( fgets(line, MAX_CHAR, fd) != NULL ) {
        dup=get_duplicate(line);
        priority=dup+1;
        printf("\n%s\nDuplicate: %d \n\n",line,dup);
        i++;
        sum_priorities=sum_priorities+priority;
        for(j=0; j<=N_ITEMS; j++) 
            inventory[j]=-1;
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
