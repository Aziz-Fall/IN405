#ifndef COM_PROCESS_H
#define COM_PROCESS_H 

#define INPUT         1
#define OUTPUT        0
#define NB_DESCRIPTOR 2
#define BUFFER_READ 255
#define COUNT_CHAR    1
#define COUNT_WORD    2 
#define COUNT_SEP     3

#include "../file_manager/file_manager.h"
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * Creat pipes 
 * @param pipes pipe communication 
 * @param nb_pipes 
 */
void creat_pipes(int pipes[][NB_DESCRIPTOR], int nb_pipes);

/**
 * Write a message in the pipe
 * @param pipe[] the pipe
 * @param *message message to write in the pipe
 */
void write_pipe(int pipe[], char *message);

/** 
 * Read the output pipe
 * @param pipe[] the pipe
 * @return the messages readed
 */
char *read_pipe(int pipe[]);

/**
 * Read the message sended to producter and print the results.
 * @param pipe[][] array pipe.
 */
void print_results_worker(int pipe[][NB_DESCRIPTOR]);

/**
 * Set a work to all producters.
 * @param pipe[][] array pipe.
 * @param Tab_File array to file 
 * @param nb_producter number producters
 */
void set_work(int pipes[][NB_DESCRIPTOR], Tab_File tab, int nb_producter);

/**
 * the process receive the work that should do and do them.
 * @param pipes pipe.
 * @param directory name directory 
 * @param option COUNT_CHAR, COUNT_SEP, COUNT_WORD
 */
void producter_work(int pipes[], char *directory, int option, int pipes_collector[]);

/**
 * Print the results sended by all producters.
 * @param pipe[][] array pipe.
 * @param nb_producter number producters
 */
void collector_work(int pipes_collector[][NB_DESCRIPTOR], int nb_producter);

/**
 * The client set the command.
 * @param nb_process numbers process.
 * @param Tab_file   lists files.
 * @param option    count char or word or separator.
 */
void work_now(int nb_process, Tab_File tab, int option);

/**
 * Set count type
 * @param count_type
 * @return int count type
 */
int set_option(char *count_type);
#endif