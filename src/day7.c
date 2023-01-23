#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_SUBD 10
#define MAX_CHAR 25
#define N_LEN 20

struct Directory
{
    unsigned char name[N_LEN];
    unsigned long size;
    unsigned char is_file;
    struct Directory *children[MAX_SUBD];
    struct Directory *parent;
    unsigned char n_children;
};

struct Directory *root_dir;
struct Directory *pwd;
unsigned char line[MAX_CHAR];
unsigned char arg0[N_LEN],arg[N_LEN];
struct Directory *subd;
struct Directory *new_dir;
unsigned long filtered_sum=0;

void print_dir(struct Directory *dir) {
    unsigned char i;
    printf("  ");
    printf("%s,%d ", dir->name,dir->is_file);
    printf("size: %lu", dir->size);
    if (dir->parent != NULL)
        printf(" parent: %s", dir->parent->name);
    printf("\n");
    for (i=0; i<dir->n_children; i++)
    {
        print_dir( dir->children[i] );
    }
}

void sum_dirs(struct Directory *dir, long max) {
    unsigned long sum=0;
    int i;
    printf("sum=%lu, %s\n", sum, dir->name);
    for(i=0; i<dir->n_children; i++) {
        if (dir->children[i]->is_file==0)
            sum_dirs(dir->children[i], max);
        sum=sum+dir->children[i]->size;
    }
    dir->size=sum;
    if(sum<=max) {
        filtered_sum+=sum;
    }
    sum=0;
}

struct Directory* get_root() {
    if (root_dir==NULL) {

        root_dir=malloc(sizeof(struct Directory));
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

struct Directory* get_subdir(char name[] ) {
    int i;
    for (i=0; i<pwd->n_children; i++)
    {
        subd=pwd->children[i];
        if( strcmp(subd->name, name)==0 ) {
            //printf("[%s] exists\n", subd->name);
            return subd;
        }
    }
    //printf("sizeof: %d\n", sizeof(struct Directory));
    subd=malloc(sizeof(struct Directory));
    if (subd==NULL) {
        printf("Unable to allocate memory" );
        exit(1);
    }
    strncpy(subd->name,name,N_LEN);
    subd->is_file=0;
    subd->parent=pwd;
    pwd->children[pwd->n_children]=subd;
    pwd->n_children++;
    //printf("creating [%s]\n",subd->name);
    return subd;
}

int parse_command(char line[]) {
    unsigned long size;

    sscanf(line, "$ %s %s\n",arg0, arg);
    //printf("process: [%s,%s]\n", command, arg);
    if(strncmp(line, "$ cd /",6)==0) {
        pwd=get_root();
        //printf("cd %s\n", pwd->name);
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
        //printf("cd %s -> %s\n",arg, pwd->name);
        return 0;
    }
    if(strncmp(line,"$ ls", 4)==0) {
        //printf("ls\n");
        return 0;
    }
    if(strncmp(line,"dir",3)==0) {
        printf("%s",line);
        sscanf(line, "%s %s\n",arg0, arg);
        if (strlen(arg)>0) {
            new_dir=get_subdir(arg);
            new_dir->is_file=0;
        }
        //printf("dir: %d, %s\n", pwd->n_children, pwd->name);
        return 0;
    }
    sscanf(line, "%s %s\n",arg0, arg);
    //printf("size: %s\n", arg0);
    size=atol(arg0);
    new_dir=get_subdir(arg);
    new_dir->is_file=1;
    new_dir->size=size;
    //printf("file: %s, %lu\n", new_dir->parent->name, new_dir->size);
    return 0;
}

int main(void)
{
    FILE *fd;

    fd=fopen("DATA.TXT","r");
    printf("Read data\n");
    while(fgets(line, MAX_CHAR, fd)!=NULL) {
        parse_command(line);
    }
    fclose(fd);
    sum_dirs(root_dir, 100000);
    print_dir(root_dir);
    printf("filtered sum= %lu",filtered_sum);
    cgetc();
    return 0;
}
