#include "count.word.h"

/**
 * check if arg is null
 * @return boolean
 */
bool is_null(void* arg) { return (arg == NULL) ? true : false; }
 
/**
 * Check if arg is null and print the message error and exit
 * @param message  message error
*/
void check_error(void *arg, char *message)
{
    if(is_null(arg))
    {
        fprintf(stderr, "%s :(\n", message);
        exit(EXIT_FAILURE);
    }
}


typedef struct Binary_tree
{
    char *word;
    int frequence;
    struct Binary_tree *left;
    struct Binary_tree *right;
}Word_tree;

Word_tree *creat_word_tree()
{
    return NULL;
}

void set_result_word_tree(Word_tree *t, FILE *file)
{
    if(is_null(t))
        return;
    
    set_result_word_tree(t->left, file);
    fprintf(file, "%30s freq: %d\n", t->word, t->frequence);
    set_result_word_tree(t->right, file);
}

Word_tree *add_word(Word_tree *t, const char *word)
{
    if(is_null(t))
    {
        t = malloc(sizeof(Word_tree));
        check_error(t, "Cant add element");
        
        t->word = malloc(sizeof(char) * (strlen(word) + 1));
        check_error(t->word, "Cant add element");
        
        strcpy(t->word, word);
        t->frequence = 1;
        t->left = t->right = NULL;
    }
    else if(strcmp(word, t->word) < 0) t->left  = add_word(t->left, word);
    else if(strcmp(word, t->word) > 0) t->right = add_word(t->right, word);
    else ++(t->frequence);

    return t;
}

void free_word_tree(Word_tree *t)
{
    if(!is_null(t))
    {
        free(t->word);
        free_word_tree(t->right);
        free_word_tree(t->left);
    }
    free(t);
}
