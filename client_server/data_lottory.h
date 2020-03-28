#ifndef DATA_LOTTORY_H
#define DATA_LOTTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER 255  

/**
 * Open file
 * @param name_file
 */
FILE *open_file(char *name_file);
/**
 * Recover the matchs numbers.
 * @param f FILE
 */
int get_match_number(FILE *f);

/**
 * Recover the number's lottory 
 * @param f FILE 
 * @param match_number 
 * @param a_num array
 */
void get_num_lottory(FILE *f, int match_number, int a_num[]);

/**
 * Recover the match gain
 * @param f FILE
 * @param match_number.
 */
int get_match_gain(FILE *f, int match_number, int nb);

/**
 * Check if client is winner
 * @param num number set by client
 * @param a_num array content good number
 * @param size size array a_num
 * @return boolean 
 */
int is_client_win(int num_client[], int a_num[], int size);

/**
 * Check if data's client is correct 
 * @param num number set by client
 * @param a_num array content good number
 * @param size size array a_num
 * @return match_number
 */
int check_match_number(int num_client[], int a_num[], int size);

#endif