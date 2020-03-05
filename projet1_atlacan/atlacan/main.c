#include "atlacan.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define FILE_ACCESSIBLE     1
#define IS_NOT_ACCESSIBLE   0
#define DIRECTORY_ACCESSIBLE 2
#define BACK ".."

int checking_accessible( char *path );
void  deep_search_atlacan( char *name_path );

int main(void)
{
    if(atl_init() != 0)
    {
        perror( "alt_init" );
        return EXIT_FAILURE;
    }
    printf("*****************************************************************************\n");
    
    char **path; int num = 0;
    atl_ls( &path, &num );
    
    for (int i = 0; i < num; i++ )
        deep_search_atlacan( path[i] );

    printf("*****************************************************************************\n");
    atl_free_ls( path, num );
    atl_fini();
    return EXIT_SUCCESS;
}


int checking_accessible( char *path )
{
    struct atl_stat stat_buffer;

    if(atl_stat(path, &stat_buffer) == 1) return IS_NOT_ACCESSIBLE;

    else if( atl_is_dir( stat_buffer.mode ) && !atl_is_link( stat_buffer.mode ) )
        return DIRECTORY_ACCESSIBLE;
    else if( atl_is_file( stat_buffer.mode ) && atl_is_ormode( stat_buffer.mode ) )
        return FILE_ACCESSIBLE;

    return IS_NOT_ACCESSIBLE;
}

void deep_search_atlacan( char *name_path )
{
    int check = checking_accessible( name_path );
    if( check == DIRECTORY_ACCESSIBLE )
    {
        atl_cd( name_path );
        char **path; int number_entry = 0;
        atl_ls( &path, &number_entry );

        for( int i = 0; i < number_entry; i++ )
            deep_search_atlacan( path[i] );

        atl_cd( BACK );
        atl_free_ls( path, number_entry );
    }
    else if( check == FILE_ACCESSIBLE )
    {
        int data = 0;
        atl_cat( name_path, &data );
        return;
    }
}
