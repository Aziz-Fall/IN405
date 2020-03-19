#include "check_command.h"

bool check_command(char *com)
{
    if( strcmp(com, "wpc") == 0 )
        return true;

    fprintf(stderr, "Unknow command: %s :|\n", com);
    return false;
}

bool check_nb_process(char *nb_process)
{
    int n = atoi(nb_process);

    if( n >= 0 && n <= MAX_PROCESS )
        return true;

    fprintf(stderr, "Number process is invalid :|\n");
    return false;
}

bool check_size(char *bloc_size)
{
    int size = atoi(bloc_size);

    if( size > 0 && size <= SIZE_MAX_ )
        return true;
    
    fprintf(stderr, "Size blocs is invalid :|\n");
    return false;
}
bool check_count_type(char *tc)
{
    if( strcmp(tc, "c") == 0 || strcmp(tc, "s") == 0 || strcmp(tc, "w") == 0 )
        return true;
    
    fprintf(stderr, "Unknow count type: %s :|\n", tc);
    return false;
}

bool list_files(char *lists)
{
    struct stat s;
    if( stat(lists, &s) != 0 )
    {
        perror("stat()");
        return false;
    }

    if( S_ISDIR(s.st_mode)) return true;

    fprintf(stderr, "Is not a directory: %s :|\n", lists);
    return false;
}
bool is_command_valid(char **argv)
{
    if( check_command(argv[1]) && check_count_type(argv[2]) && check_nb_process(argv[3]) && check_size(argv[4]) && list_files(argv[5]) )
        return true;
    return false;
}