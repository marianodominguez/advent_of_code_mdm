#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_SUBD 10
#define MAX_CHAR 25
#define N_LEN 10

struct Directory
{
    char name[N_LEN];
    unsigned long size;
    unsigned char is_file;
    struct Directory *children[MAX_SUBD];
    struct Directory *parent;
    int n_children;
};

struct Directory *root_dir;
struct Directory *pwd;
char line[MAX_CHAR];
char arg0[N_LEN],arg[N_LEN];
struct Directory *subd;
struct Directory *new_dir;

void print_dir(struct Directory *dir) {
    unsigned char i;
    printf("%s", dir->name);
    if (dir->is_file == 1)
        printf(" %lu", dir->size);
    printf("\n");
    for (i=0; i<dir->n_children; i++)
    {
        printf("  ");
        print_dir( dir->children[i] );
    }
}

/*
unsigned long get_big_dirs(struct Directory *dir, long max) {
    int i;
    struct Directory *current;
    unsigned long sum =0;
    for(i=0; i<dir->n_children; i++) {
        sum=sum+dir->children[i];
    }
    return sum;
}
*/

struct Directory* get_root() {
    if (root_dir==NULL) {

        root_dir=(struct Directory *) malloc(sizeof(struct Directory));
        if (root_dir==NULL) {
            printf("Unable to allocate memory" );
            exit(1);
        }
        strcpy(root_dir->name, "root");
        root_dir->parent=NULL;
        root_dir->is_file=0;
        root_dir->n_children=0;
        root_dir->size=0;
    }
    return root_dir;
}

struct Directory* get_subdir(char* name ) {
    int i;
    for (i=0; i<pwd->n_children; i++)
    {
        subd=pwd->children[i];
        if( strcmp(subd->name, name)==0 ) {
            printf("[%s] exists\n", subd->name);
            return subd;
        }
    }
    //printf("sizeof: %d\n", sizeof(struct Directory));
    subd=(struct Directory *)malloc(sizeof(struct Directory));
    if (subd==NULL) {
        printf("Unable to allocate memory" );
        exit(1);
    }
    strncpy(subd->name,name,N_LEN);
    subd->is_file=0;
    subd->parent=pwd;
    pwd->children[pwd->n_children]=subd;
    pwd->n_children++;
    printf("creating [%s], %s\n", subd->name, subd->parent->name);
    return subd;
}

int parse_command(char line[]) {
    unsigned long size;

    sscanf(line, "$ %s %s\n",arg0, arg);
    //printf("process: [%s,%s]\n", command, arg);
    if(strncmp(line, "$ cd /",6)==0) {
        pwd=get_root();
        printf("cd %s\n", pwd->name);
        return 0;
    }
    if(strncmp(line, "$ cd ..",6)==0) {
        if(pwd->parent!=NULL) 
            pwd=pwd->parent;
        printf("cd ..-> %s\n", pwd->name);
        return 0;
    }
    if(strncmp(line,"$ cd",4)==0) {
        pwd=get_subdir(arg);
        printf("cd %s -> %s\n",arg, pwd->name);
        return 0;
    }
    if(strncmp(line,"$ ls", 4)==0) {
        printf("ls\n");
        return 0;
    }
    if(strncmp(line,"dir",3)==0) {
        printf("%s",line);
        sscanf(line, "%s %s\n",arg0, arg);
        if (strlen(arg)>0) {
            new_dir=get_subdir(arg);
            new_dir->is_file=0;
        }
        printf("dir: %d, %s\n", pwd->n_children, pwd->name);
        return 0;
    }
    sscanf(line, "%s %s\n",arg0, arg);
    size=atol(arg0);
    printf("size: %lu\n", size);
    new_dir=get_subdir(arg);
    new_dir->is_file=1;
    new_dir->size=size;
    printf("file: %s, %lu\n", new_dir->parent->name, new_dir->size);
    return 0;
}

int main(void)
{
    FILE *fd;

    fd=fopen("/home/mariano/advent_of_code_2022/resources/test_data7.txt","r");
    printf("Read data\n");
    while(fgets(line, MAX_CHAR, fd)!=NULL) {
        parse_command(line);
    }
    fclose(fd);
    print_dir(root_dir);

    getc(stdin);
    return 0;
}
