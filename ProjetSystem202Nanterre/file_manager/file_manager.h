#ifndef FILE_MANAGER__H
#define FILE_MANAGER__H

#define SIZE_LINE 1024
#define SIZE_WORD   50

#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include "../count_char/count_char.h"
#include "../count_word/count.word.h"

typedef struct File
{
    int length;
    char *name;  
}File;

struct Tab_File
{
    int number_file;
    File *file;
};
/**
 * Définition du typde Tab_File: tableau de fichier.
 */
typedef struct Tab_File Tab_File;

/**
 * Créer, ouvrir un ficher et le retourne
 * @param name name file
 * @param mode mode
 * @return FILE file
 */
FILE *open_file(char *name_file , char *mode);

/**
 * Print the content of the file passed in argument.
 * @param file file
 * @param num_file the index of the file.
 */
void print_content_file(FILE* file, int num_file);

/**
 * Ecrire dans un fichier.
 * @param file file 
 * @param string string to put in the file
 */
void write_file(FILE* file, char *string);

/**
 * Fermer un fichier.
 * @param file file to close
 */
void close_file(FILE *file);

/**
 * Retourner un tableau de fichier, lu à partir d'un dossier.
 * @param name_directory
 * @return array contenented the lists files
 */
Tab_File assigne_tab_file(char *name_directory);
    
/**
 * Créer et initialiser un tableau de fichier.
 * @return struct 
 */
Tab_File init_tab_file();

/**
 * Ouvrir un dossier et retourne le nom du dossier ouvert.
 * @param directory_name name directory to open
 * @return pointer dir
 */
DIR *open_directory(char *directory_name);

/**
 * Affiche un message d'erreur s'il y'a erreur.
 * @param e argument to check
 * @param message message to print if e throws error
 */
void error(void *e, char *message);

/**
 * Free thr memory alocated for the files.
 * @param tab_f array of files
 */
void free_tab_file(Tab_File tab_f);

/**
 * Count numbers occurences characters in file 
 * @param FILE a file
 * @param name_file_result
 */
void count_nb_occurence_char(FILE *file, char *name_file_result);

/**
 * Count numbers occurences separator in file 
 * @param FILE a file
 * @param name_file_result
 */
void count_nb_occurence_separator(FILE *file, char *name_file_result);

/**
 * Count numbers occurences words in file 
 * @param FILE a file
 * @param name_file_result
 */
void count_nb_occurence_word(FILE *file, char *name_file_result);

#endif
