#include "com_process.h"

void creat_pipes(int pipes[][NB_DESCRIPTOR], int nb_pipes)
{
    if(nb_pipes <= 0)
    {
        printf("nb_pipes can't be negative.");
        return;
    }
    for( int i = 0; i < nb_pipes; i++ )
    {
        if( pipe(pipes[i]) < 0 )
        {
            perror("pipe() creat");
            return;
        }
    }
}
void write_pipe(int pipe[], char *message)
{
    if( close(pipe[OUTPUT]) < 0)
    {
        perror("close() in pipe");
        return;
    }

    if( write(pipe[INPUT], message, strlen(message)) < strlen(message))
    {
        perror("write() in pipe");
        return;
    }
}

char *read_pipe(int pipe[])
{
    if( close(pipe[INPUT]) < 0 )
    {
        perror("close() in pipe");
        exit(EXIT_FAILURE);
    }
    
    static char buffer_read[BUFFER_READ] = {0};

    if(read(pipe[OUTPUT], buffer_read, BUFFER_READ) < 0)
    {
        perror("read() in pipe in com_process");
        exit(EXIT_SUCCESS);
    }
    return buffer_read;
}

void print_results_worker(int pipes[][NB_DESCRIPTOR])
{
    return;
}

void set_work(int pipes[][NB_DESCRIPTOR], Tab_File tab, int nb_producter)
{
    for(int i = 0; i < nb_producter; i++)
        write_pipe(pipes[i], tab.file[i].name);
    
    free_tab_file(tab);
}

void producter_work(int pipes[], char *directory, int option, int pipes_collector[])
{
    char *buffer = NULL, name_file_complet[BUFFER_READ] = {0};

    buffer = read_pipe(pipes);

    if( sprintf(name_file_complet, "%s/%s", directory, buffer) < 0)
    {
        perror("sprintf()");
        return;
    } 

    FILE *f = open_file(name_file_complet, "r");

    switch (option)
    {
    case COUNT_CHAR:
        count_nb_occurence_char(f, buffer);
        break;
    case COUNT_SEP:
        count_nb_occurence_separator(f, buffer);
    case COUNT_WORD:
        count_nb_occurence_word(f, buffer);
        break;
    default:
        printf("The option does not exist :|\n");
        break;
    }
    
    char file_result[BUFFER_READ] = {0};
    if( sprintf(file_result, "result_count/%s", buffer) < 0)
    {
        perror("sprintf()");
        return;
    }
    write_pipe(pipes_collector, file_result);
    close_file(f);
}

void collector_work(int pipes_collector[][NB_DESCRIPTOR], int nb_producter)
{
    for(int i = 0; i < nb_producter; i++)
    {
        char *buffer_read = NULL;
        buffer_read = read_pipe(pipes_collector[i]);
        FILE *f = fopen(buffer_read, "r");
        print_content_file(f, i);
        close_file(f);
    }
}

void work_now(int nb_process, Tab_File tab, int option)
{
    int pipes[nb_process][NB_DESCRIPTOR], pipes_collector[nb_process][NB_DESCRIPTOR];
    creat_pipes(pipes_collector, nb_process);
    creat_pipes(pipes, nb_process);
    pid_t pid_son;
    int all_process = nb_process + 2;
    for(int i = 0; i < all_process; i++)
    {
        if((pid_son = fork()) == 0)
        {
            if( i == 0)
            {
                set_work(pipes, tab, nb_process);
                return;
            }
            else if( i == (all_process - 1) )
            {
                collector_work(pipes_collector, nb_process);
                return;
            }
            else 
            {
                producter_work(pipes[i - 1], "files", option, pipes_collector[i - 1]);
                return;
            }
            
        }
        else 
        {
            printf("PID parent: %d PID son: %d\n", getpid(), pid_son);
        }
    }
    for(int i = 0; i < all_process; i++) 
        wait(NULL);
}

int set_option(char *count_type)
{
    if( strcmp(count_type, "c") == 0 )
        return COUNT_CHAR;
    
    if( strcmp(count_type, "w") == 0 )
        return COUNT_WORD;
    
    if( strcmp(count_type, "s") == 0 )
        return COUNT_SEP;
    
    return COUNT_CHAR;
}