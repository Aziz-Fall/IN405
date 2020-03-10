#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "lexc.h"

#define ACTION_SIZE 16
#define NAME_LEXICON_SIZE 50
#define WORD_SIZE   48
#define LEXC_INIT   "lexc_init"
#define LEXC_ADD    "lexc_add"
#define LEXC_REMOVE "lexc_remove"
#define LEXC_CHECK  "lexc_check"
#define LEXC_LIST   "lexc_list"
#define QUIT        "quit"

/**
 * Defines type boolean
 */
typedef enum
{
    false,
    true
}Bool;

/**
 * checked arg if arg is null or not
 * @param arg 
 * @return boolean
*/
Bool is_null(void *arg)
{
    return (arg == NULL) ? true : false;
}

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

/**
 * Define binary tree 
*/
typedef struct Binary_tree
{
    char *word;
    struct Binary_tree *left;
    struct Binary_tree *right;
}Tree;

/**
 * Creat a binary tree empty
 * @return null
*/
Tree *creat_tree()
{
    return NULL;
}

/**
 * Print the containt of binary
 * @param t: binary tree.
*/
void print_tree(Tree *t)
{
    if(is_null(t))
        return;
    
    print_tree(t->left);
    printf("\t%s\n", t->word);
    print_tree(t->right);
}

/**
 * Return the word that length is longer than other words
 * @param t tree
 * @return word
*/
char *max(Tree *t)
{
    if(is_null(t->right)) return t->word;
    return max(t->right);
}
/**
 * Delete word in the tree
 * @param t: tree
 * @param word 
 * @return t
*/
Tree *delete_word( Tree *t, const char *word )
{
    if(is_null(t)) return t;
    if(strcmp(word, t->word) > 0) t->right = delete_word(t->right, word);
    else if(strcmp(word, t->word) < 0) t->left  = delete_word(t->left, word);
    else 
    {
        if(is_null(t->left))
        {
            Tree *tmp = t;
            t = t->right;
            free(tmp->word);
            free(tmp);
            return t;
        }
        if(is_null(t->right))
        {
            Tree *tmp = t;
            t = t->left;
            free(tmp->word);
            free(tmp);
            return t;   
        }
        else 
        {
            char *w = max(t->left);
            t->word = realloc(t->word, strlen(w) + 1);
            check_error(t->word, "Cant delete element");
            strcpy(t->word, w);
            t->left = delete_word(t->left, w);
        }
    } 

    return t;
}

/**
 * Add element in the tree
 * @param t : tree
 * @param word 
 * @return t
*/
Tree *add_element(Tree *t, const char *word)
{
    if(is_null(t))
    {
        t = malloc(sizeof(Tree));
        check_error(t, "Cant add element");
        
        t->word = malloc(sizeof(char) * (strlen(word) + 1));
        check_error(t->word, "Cant add element");
        
        strcpy(t->word, word);
        t->left = t->right = NULL;
    }
    else if(strcmp(word, t->word) < 0) t->left  = add_element(t->left, word);
    else if(strcmp(word, t->word) > 0) t->right = add_element(t->right, word);

    return t;
}

/**
 * Check if arg is in the tree
 * @param tree
 * @param arg
 * @return boolean
*/

Bool is_in_tree(Tree *t, const char *word)
{
    if(is_null(t)) return false;
    if(strcmp(t->word, word) == 0) return true;
    return is_in_tree(t->left, word) || is_in_tree(t->right, word); 
} 

/**
 * Free the memory allocated
*/
void free_tree(Tree *t)
{
    if(!is_null(t))
    {
        free(t->word);
        free_tree(t->right);
        free_tree(t->left);
    }
    free(t);
}

/**
 * Defines a lexicon.
 */
 typedef struct lexc
 {
    Tree *tree;
    char *name_lexicon;
    Bool is_mutable;
    int nb_word;
 }Lexc;

/**
 * Initializes a lexicon data structure.
 * 
 * The lexicon must be freed using the lexc_fini() function.
 *
 * @param[in]  name             Lexicon name.
 * @param[in]  mutable          TRUE if the lexicon is mutable.
 *
 * @return     New lexicon.
 */
struct lexc *lexc_init(const char *name, const int mutable)
{   

    Lexc *l = malloc(sizeof(Lexc));
    check_error(l, "Cant creat lexique");
    l->name_lexicon = malloc( (sizeof(name) + 1) );
    check_error(l->name_lexicon, "Cant init name lexicon");
    strcpy(l->name_lexicon, name);
    l->nb_word    = 0;
    l->is_mutable = (Bool)mutable;
    l->tree       = creat_tree();
    return l;
}

/**
 * Releases a lexicon data structure.
 *
 * @param      lexc             Lexicon to release.
 */
void lexc_fini(struct lexc *lexc)
{
    check_error(lexc, "Cant free lexicon, lexicon is empty");
    free_tree(lexc->tree);
    free(lexc->name_lexicon);
    free(lexc);
}

/**
 * Add the argument word in lexicon
 * @param lexc lexicon
 * @param word 
 * @return 0 on success 1 on failed
*/
int lexc_add(struct lexc *lexc, const char *word)
{
    if(lexc->is_mutable && lexc_check(lexc, word))
    {
        lexc->tree = add_element(lexc->tree, word);
        ++(lexc->nb_word);
        return 0;
    }
    return 1;
}

/**
 * Intrepret the the argument cmd
 * @param lexc lexicon
 * @param cmd command 
 * @return 0 on success 1 on failed
*/
int cmd_interpret(struct lexc **lexc, const char *cmd)
{
    int i;
    char action[ACTION_SIZE] = {'\0'}, word[WORD_SIZE] = {'\0'};

    for(i = 0; cmd[i] != 32 && i < strlen(cmd); i++) action[i] = cmd[i];
    i++;
    for(int j = 0; i < strlen(cmd); word[j++] = cmd[i++]);

    if(strcmp(action, LEXC_INIT) == 0) 
    {
        if(!is_null(*lexc))
        {
            printf("échec :(\n");
            return EXIT_SUCCESS;
        }
        (*lexc) = lexc_init(word, 1);
        printf("succés.\n");
        return EXIT_SUCCESS;
    }
    else if(strcmp(action, LEXC_ADD) == 0) 
    {
        if(!lexc_add((*lexc), word))
            printf("succès.\n");
        else 
            printf("échec.\n");
        return EXIT_SUCCESS;
    }
    else if(strcmp(action, LEXC_REMOVE) == 0) 
    {
        if(lexc_remove((*lexc), word))
            printf("échec.\n");
        else 
            printf("succès.\n");
        return EXIT_SUCCESS;
    }
    else if(strcmp(action, LEXC_CHECK) == 0) 
    {
        if(lexc_check((*lexc), word))
            printf("échec.\n");
        else 
            printf("succés.\n");
        return EXIT_SUCCESS;
    }
    else if(strcmp(action, LEXC_LIST) == 0)
    {
        lexc_list((*lexc));
        return EXIT_SUCCESS;
    }
    else if(strcmp(action, QUIT) == 0) return EXIT_FAILURE; 
    
    printf("Unkown command :(\n");

    return 0;
}

/**
 * Remove the argument word in lexicon
 * @param lexc lexicon
 * @param word 
 * @return 0 on success 1 on failed
*/
int lexc_remove(struct lexc *lexc, const char *word)
{
    if(!is_null(lexc) && lexc->is_mutable && !lexc_check(lexc, word))
    {
        lexc->tree = delete_word(lexc->tree, word);
        --(lexc->nb_word);
        return 0;
    }
    return 1;
}

/**
 * Check the argument word in lexicon
 * @param lexc lexicon
 * @param word 
 * @return 0 on success 1 on failed
*/
int lexc_check(struct lexc *lexc, const char *word)
{
    if(!is_null(lexc) && is_in_tree(lexc->tree, word))  return 0;
    return 1;
}

/**
 * Intrepret the the argument cmd
 * @param lexc lexicon
 * @param cmd command 
 * @return 0 on success 1 on failed
*/
int cmd_interpret_bis(void *tab_lexicon[], const char *cmd, int nb_lexicon)//Aller plus loin.
{
    int i, p;
    Bool is_here = true;
    char action[ACTION_SIZE] = {'\0'}, word[WORD_SIZE] = {'\0'}, name_lexcicon[NAME_LEXICON_SIZE] = {'\0'};

    for(i = 0; cmd[i] != 32; i++) name_lexcicon[i] = cmd[i];
    i++;
    for(int j = 0; cmd[i] != 32; j++) action[j] = cmd[i++];
    i++;
    for(int j = 0; i < strlen(cmd); word[j++] = cmd[i++]);

    while(p < nb_lexicon && is_here)
    {
        if(strcmp(*tab_lexicon, name_lexcicon) == 0)
            is_here = false;
        p++;
    }
    if(!is_here)
    {
        if(strcmp(action, LEXC_INIT) == 0) 
        {
            tab_lexicon[p - 1] = lexc_init(word, 1);
            return EXIT_SUCCESS;
        }
        else if(strcmp(action, LEXC_ADD) == 0) 
        {
            return lexc_add(tab_lexicon[p - 1], word);
        }
        else if(strcmp(action, LEXC_REMOVE) == 0) 
        {
            return lexc_remove(tab_lexicon[p - 1], word);
        }
        else if(strcmp(action, LEXC_CHECK) == 0) 
        {
            return lexc_check(tab_lexicon[p - 1], word);
        }
        else if(strcmp(action, QUIT) == 0) exit(EXIT_SUCCESS);
    } 
    
    printf("Unkown command :(\n");

    return 1;
}



/**
 * List the content lexicon
 * @param lexc lexicon
*/
void lexc_list(Lexc *lexc)
{
    if(is_null(lexc))
    {
        fprintf(stderr, "Cant list lexicon: lexicon is empty");
        return;
    }
    printf("*************************************************\n");
    printf("*");
    printf("%25s\t\t\t*\n", lexc->name_lexicon);
    printf("*************************************************\n");
    print_tree(lexc->tree);
    printf("*************************************************\n");
    printf("*-Nb_element = %d\t\t\t\t*\n*-Is mutalbe = %d\t\t\t\t*\n", lexc->nb_word, (int)lexc->is_mutable);
    printf("*************************************************\n");
}