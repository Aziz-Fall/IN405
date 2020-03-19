#include "count_char.h"

/**
 * check if arg is null
 * @return boolean
 */
bool is_null_(void* arg) { return (arg == NULL) ? true : false; }

/**
 * Check if arg is null and print the message error and exit
 * @param message  message error
*/
void check_error_(void *arg, char *message)
{
    if(is_null_(arg))
    {
        fprintf(stderr, "%s :(\n", message);
        exit(EXIT_FAILURE);
    }
}


typedef struct Binary_tree
{
    char character;
    int frequence;
    struct Binary_tree *left;
    struct Binary_tree *right;
}Char_tree;

Char_tree *creat_tree()
{
    return NULL;
}

void set_result_tree(Char_tree *t, FILE *file)
{
    if(is_null_(t))
        return;

    set_result_tree(t->left, file);
    fprintf(file, "%c freq: %d\n", t->character, t->frequence);
    set_result_tree(t->right, file);
}


Char_tree *add_char(Char_tree *t, const char c)
{
    if(is_null_(t))
    {
        t = malloc(sizeof(Char_tree));
        check_error_(t, "Cant add element");
        
        t->character = c;
        t->frequence = 1;
        t->left = t->right = NULL;
    }
    else if(c < t->character) t->left  = add_char(t->left, c);
    else if(c > t->character) t->right = add_char(t->right, c);
    else ++(t->frequence);

    return t;
}

void free_tree(Char_tree *t)
{
    if(!is_null_(t))
    {
        free_tree(t->right);
        free_tree(t->left);
    }
    free(t);
}
