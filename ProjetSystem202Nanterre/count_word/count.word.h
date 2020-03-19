#ifndef COUNT_WORD_H
#define COUNT_WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Define binary tree 
*/
typedef struct Binary_tree Word_tree;

/**
 * Creat a binary tree empty
 * @return null
*/
Word_tree *creat_word_tree();

/**
 * Print the containt of binary
 * @param t: binary tree.
*/
void set_result_word_tree(Word_tree *t, FILE *file);

/**
 * Add element in the tree
 * @param t : tree
 * @param word 
 * @return t
*/
Word_tree *add_word(Word_tree *t, const char *word);


void free_word_tree(Word_tree *t);

#endif