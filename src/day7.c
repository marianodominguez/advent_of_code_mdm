#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_SUBD 100
#define MAX_CHAR 255

struct Directory
{
    char name[10];
    int size;
    char is_file;
    struct Directory *children[MAX_SUBD];
    struct Directory *parent;
    int n_children;
};

struct Directory *root_dir;
struct Directory* pwd;

unsigned char line[255];

void print_dir(struct Directory *dir) {
    int i;
    printf("%s\n", dir->name);
    for (i=0; i<dir->n_children; i++)
    {
        print_dir( dir->children[i] );
    }
    
}

struct Directory* get_root() {
    if (root_dir==NULL) {
        root_dir=malloc(sizeof(struct Directory));
        if (root_dir==NULL) {
            printf("Unable to allocate memory" );
            exit(1);
        }

        strcpy(root_dir->name, "/");
        root_dir->is_file=0;
    }
    return root_dir;
}

struct Directory* get_subdir(struct Directory *pwd, char * name ) {
    struct Directory *subd;
    int i;
    for (i=0; i<pwd->n_children; i++)
    {
        subd=pwd->children[i];
        if( strcmp(subd->name, name)==0 ) {
            return subd;
        }
    }
    subd=malloc(sizeof(struct Directory));
    if (subd==NULL) {
        printf("Unable to allocate memory" );
        exit(1);
    }
    strcpy(subd->name,name);
    subd->is_file=0;
    pwd->n_children++;
    pwd->children[pwd->n_children]=subd;
    subd->parent=pwd;
    return subd;
}


int parse_command(char * line) {
    unsigned char* command,arg;
    int n,size;
    struct Directory *new_dir;
    
    sscanf(line, "$ %s %s",command, arg);
    printf("process: [%s,%s]\n", command, arg);
    if(strncmp(line, "$ cd /",5)==0) {
        root_dir=get_root();
        pwd=root_dir;
        printf("cd %s\n", pwd->name);
        return 0;
    }
    if(strncmp(line, "$ cd ..",6)==0) {
        if(pwd->parent!=NULL) 
            pwd=pwd->parent;
        printf("pwd %s", pwd->name);
        return 0;
    }
    if(strncmp(line,"$ cd",4)==0) {
        pwd=get_subdir(pwd, &arg);
        printf("pwd %s", pwd->name);
        return 0;
    }
    if(strncmp(command,"$ ls", 4)==0) {
        return 0;
    }
    if(strncmp(command,"dir",3)==0) {
        new_dir=get_subdir(pwd,&arg);
        n=pwd->n_children;
        pwd->n_children++;
        pwd->children[n]=new_dir;
        printf("dir: %d", pwd->n_children);
        return 0;
    }
    sscanf(line, "%s %s",command, arg);
    size=atoi(command);
    new_dir=get_subdir(pwd, &arg);
    new_dir->is_file=1;
    new_dir->size=size;
    printf("added: %s\n", arg);
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
    print_dir(root_dir);

    cgetc();
    return 0;
}
