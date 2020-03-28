#include "data_lottory.h"
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 255
#define NOT_EXEC              -1
#define CORRECT_EXEC_WIN       1
#define CORRECT_EXEC_NOT_WIN   0
#define CORRECT_EXEC_NOT_PLAY  2

#define SERVER  "server"
#define CLIENT  "client"

typedef struct
{
	int fd_client;
	int fd_server;
}Client_Server;

typedef struct 
{
	int n;
	char buffer[SIZE];
}Number_lottery;

Client_Server cs;
Number_lottery number_lottery;

/**
 * Manage the communication between client and server.
 * @param arg the message
 */
void *client(void *arg);

/**
 * Manage the communication between server and client.
 * @param name_file file that content valid number lottory
 */
void server(char *name_file);

/**
 * Split a string with espace
 * @param string 
 * @param tab      the array that content result of splitting string.
 * @param size_tab size array tab.
 */
void split(char *string, int tab[], int size_tab);
/**
 * Write a message using file descriptor fd.
 * @param message the message
 * @param fd      the file descriptor
 */
void write_message(char *message, int fd);

/**
 * Check if temporal file exist
 * @param path the path.
 */
int check_file_fifo_exist(char *path);

/**
 * Creat a temporal file if file does not exist.
 * @param path the path
 */
void creat_file_fifo_client(char *path);

/**
 * Creat a temporal file if file does not exist.
 * @param path the path
 */
void creat_file_fifo_server(char *path);

int main(int argc, char **argv)
{
	pthread_t pthread;
    void *return_client_value;

    if( argc >= 2 )
    {
        creat_file_fifo_client("/tmp/client");
        creat_file_fifo_server("/tmp/server");
        cs.fd_client = open("/tmp/client", O_RDWR);
	    cs.fd_server = open("/tmp/server", O_RDWR);

        if( strcmp(argv[1], CLIENT) == 0 )
        {   
            if(argc == 2 && strcmp(argv[1], CLIENT) == 0 )
            {
                printf("You does not play :|\n\n");
                close(cs.fd_client);
                close(cs.fd_server);
                return CORRECT_EXEC_NOT_PLAY;
            }
            int j = 0;
            for(int i = 2; i < argc; i++)
            {
                for( int k = 0; k < strlen(argv[i]); k++ )
                    number_lottery.buffer[j++] = argv[i][k]; //On met tous les nombres de l'argument en une chaine- 
                number_lottery.buffer[j++] = ' ';            // -de caractéres.
            }

            number_lottery.n = strlen(number_lottery.buffer);

            pthread_create(&pthread, NULL, client, &number_lottery);
        }

        if( strcmp(argv[1], SERVER) == 0 )
        {
            server( argv[2] );
        }

        pthread_join(pthread, &return_client_value);
    }

    int *return_client = return_client_value; 
	return *return_client;
}

void *client(void *arg)
{   
    int ret = 2;
	Number_lottery *number_lottery = arg;
    if( write(cs.fd_client, number_lottery->buffer, number_lottery->n) < 0 )
    {
        perror("In client, write()");
        return NULL;
    }
	close(cs.fd_client);
	char buffer[SIZE] = {0};
	if( read(cs.fd_server, buffer, SIZE) < 0 )
    {
        perror("In client, read()");
        return NULL;
    }
	close(cs.fd_server);
	printf("Client receive: %s\n", buffer);
    if( buffer[0] == 'Y' )   ret = CORRECT_EXEC_WIN;
    else if ( buffer[0] == 'B' ) ret = CORRECT_EXEC_NOT_WIN;
	pthread_exit(&ret);
}

void server(char *name_file)
{
    FILE *file = open_file(name_file);
    int size = get_match_number(file), tab[size], match_number = 0, a_num[size];
	char buffer_read[SIZE] = {0};
	if( read(cs.fd_client, buffer_read, SIZE) < 0)
    {
        perror("In server, read()");
        return;
    }
    split(buffer_read, tab, size);
    get_num_lottory(file, size, a_num);
    match_number = check_match_number(tab, a_num, size);

	printf("Server receive: %s\n", buffer_read);
        
    char buffer_r[BUFFER] = {0};
    int gain = get_match_gain(file, match_number, size);    
    
    if( is_client_win(tab, a_num, size) )
    {
        sprintf(buffer_r, "You win: [Gain: %d €, Match number: %d]\nBravo....\n", gain, match_number);
        write_message(buffer_r, cs.fd_server);
    }
    else if( match_number >= 0 && match_number <= size )
    {
        if(gain < 0) gain = 0;
        sprintf(buffer_r, "Bad Combination, number client [%s], Match number: %d, Gain: %d €\n", buffer_read, match_number, gain);
        write_message(buffer_r, cs.fd_server);
    } 
    else 
    {
        sprintf(buffer_r, "You does not play :|\n");
        write_message(buffer_r, cs.fd_server);
    }
    close(cs.fd_client);
	close(cs.fd_server);
    fclose(file);
}

void split(char *string, int tab[], int size_tab)
{
    char num[10] = {0};
    int j = 0, k = 0;
    for( int i = 0; i < strlen(string) && k < size_tab; i++)
    {
        if( isdigit(string[i]) )
            num[j++] = string[i];
        else 
        {
            j = 0;
            tab[k++] = atoi(num);
        }
    }
}

void write_message(char *message, int fd)
{
    if( write(fd, message, strlen(message)) < 0 )
    {
        perror("Write()");
        exit(-1);
    }
}

int check_file_fifo_exist(char *path)
{
    struct stat s;
    if( stat(path, &s) == 0 )
        return 1;
    return 0;
}

void creat_file_fifo_client(char *path)
{
    if( !check_file_fifo_exist(path) )
    {
        if( mkfifo("/tmp/client", 0755) < 0 )
        {
            perror("mkfifo() ");
            exit(NOT_EXEC);
        }
    }
}

void creat_file_fifo_server(char *path)
{
    if( !check_file_fifo_exist(path) )
    {
        if( mkfifo("/tmp/server", 0755) < 0 )
        {
            perror("mkfifo() ");
            exit(NOT_EXEC);
        }
    }
}
