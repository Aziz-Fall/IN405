#ifndef __H_LEXC__
#define __H_LEXC__

#define COMMAND_SIZE 50
/**
 * Defines a lexicon.
 */
typedef struct lexc Lexc;

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
struct lexc *lexc_init(const char *name, const int mutable);

/**
 * Releases a lexicon data structure.
 *
 * @param      lexc             Lexicon to release.
 */
void lexc_fini(Lexc *lexc);

int lexc_add(struct lexc *lexc, const char *word);
int lexc_remove(struct lexc *lexc, const char *word);
int lexc_check(struct lexc *lexc, const char *word);
void lexc_list(struct lexc *l);

int cmd_interpret_bis(void**, const char *cmd, int nb_lexicon);
int cmd_interpret(struct lexc **lexc, const char *cmd);
#endif