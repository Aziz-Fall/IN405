#include "atlacan.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define FILE_ACCESSIBLE     1
#define IS_NOT_ACCESSIBLE   0
#define DIRECTORY_ACCESSIBLE 2
#define BACK ".."

int checking_accessible(char *path);
void  deep_search_atlacan(char *name_path);
int main(void)
{
    if(atl_init() != 0)
    {
        perror("alt_init");
        return EXIT_FAILURE;
    }
    printf("*****************************************************************************\n");
    char **path; int num = 0;
    atl_ls(&path, &num);
    for(int i = 0; i < num; i++)
    {
        printf("path racine[%d]: %s\n", i, path[i]);
        deep_search_atlacan(path[0]);
        printf("***********************************************\n\n");
    }
    

    printf("*****************************************************************************\n");
    atl_free_ls(path, num);
    atl_fini();
    return EXIT_SUCCESS;
}


int checking_accessible(char *path)
{
    struct atl_stat stat_buffer;
    if(atl_stat(path, &stat_buffer) == 1) return IS_NOT_ACCESSIBLE;
    else if(atl_is_dir(stat_buffer.mode) && !atl_is_link(stat_buffer.mode))
        return DIRECTORY_ACCESSIBLE;
    else if(atl_is_file(stat_buffer.mode))
        return FILE_ACCESSIBLE;

    return IS_NOT_ACCESSIBLE;
}

void deep_search_atlacan(char *name_path)
{
    printf("Racine[%s]\n", name_path);
    int check = checking_accessible(name_path);
    if(check == DIRECTORY_ACCESSIBLE)
    {
        atl_cd(name_path);
        char **path; int number_entry = 0;
        atl_ls(&path, &number_entry);
        for(int i = 0; i < number_entry; i++)
        {
            printf("\tr[%d] path: %s\n",i,  path[i]);
            deep_search_atlacan(path[i]);
        }
        atl_cd(BACK);
        printf("\n");
        atl_free_ls(path, number_entry);
    }
    else if(check == FILE_ACCESSIBLE)
    {
        int data = 0;
        printf("path cat: %s\n", name_path);
        atl_cat(name_path, &data);
        printf("path: %s, data : %d\n", name_path, data);
        printf("current directory: %s\n", atl_getpwd());
        return;
    }
}
