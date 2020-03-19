#ifndef COUNT_CHAR_H
#define COUNT_CHAR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * Define binary tree 
*/
typedef struct Binary_tree Char_tree;

/**
 * Creat a binary tree empty
 * @return null
*/
Char_tree *creat_tree();

/**
 * Print the containt of binary
 * @param t: binary tree.
*/
void set_result_tree(Char_tree *t, FILE *file);

/**
 * Add element in the tree
 * @param t : tree
 * @param word 
 * @return t
*/
Char_tree *add_char( Char_tree *t, const char c );

/**
 * Free the memory allocated
*/
void free_tree(Char_tree *t);

#endif 