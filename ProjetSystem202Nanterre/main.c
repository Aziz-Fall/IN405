#include "communication_process/com_process.h"
#include "check_command/check_command.h"

int main(int argc, char **argv)
{

    if( argc != 6 )
    {
        fprintf(stderr, "Less arguments :|\n");
        return EXIT_FAILURE;
    }
    if( !is_command_valid(argv) )
    {
        fprintf(stderr, "Invalid command :|\n");
        return EXIT_FAILURE;
    }

    Tab_File tab   = init_tab_file();
    tab            = assigne_tab_file(argv[5]);

    int nb_process = atoi(argv[3]);
    nb_process     = ( nb_process == 0 ) ? MIN_PROCESS : nb_process; 

    work_now(nb_process, tab, set_option(argv[2]));

    free_tab_file(tab);

    return EXIT_SUCCESS;
}