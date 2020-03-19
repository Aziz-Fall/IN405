#include "file_manager.h"

bool _is_null(void *arg)
{
    return ((arg == NULL) ? true : false);
}

FILE *open_file(char *name_file, char *mode)
{
    FILE *file = fopen(name_file, mode);

    if(_is_null(file))
    {
        fprintf(stderr, "Cant open file %s\n", name_file);
        exit(EXIT_FAILURE);
    }

    return file;
}

void print_content_file(FILE* file, int num_file)
{   
    printf("************************************\n");
    printf("The result of file: %d\n", num_file);
    printf("************************************\n");

    char buffer_read[SIZE_LINE] = {0};
    while ( fgets(buffer_read, SIZE_LINE, file) )
        printf("%s", buffer_read);
}

void close_file(FILE *file)
{
    if(fclose(file) == EOF)
    {
        fprintf(stderr, "Cant close file.\n");
        exit(EXIT_FAILURE);
    }
}

void write_file(FILE *file, char *string)
{
    int status = fputs(string, file);
    if(status == EOF)
    {
        fprintf(stderr, "Cant write in the file.\n");
        return;
    }
}

File _init_file(char *names)
{
    File f;
    f.length = strlen(names) + 1;
    f.name = (char*) malloc(sizeof(char)*f.length);
    if(_is_null(f.name))
    {
        fprintf(stderr, "Cant init file:(\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < f.length; i++)
        f.name[i] = names[i];

    return f;
}

Tab_File init_tab_file()
{
    Tab_File t;

    t.file = NULL;
    t.number_file = 0;

    return t;
}

Tab_File assigne_tab_file(char *name_directory)
{
    DIR *dire = open_directory(name_directory);
    Tab_File tab = init_tab_file();

    struct dirent *d;
    d = readdir(dire);
    while (!_is_null(d))
    {
        if(!(d->d_name[0] == '.'))
        {
            File f = _init_file(d->d_name);
            tab.file = (File *)realloc(tab.file, sizeof(File)*(tab.number_file + 1));
            error(tab.file, "Cant assign tab file");
            tab.file[tab.number_file] = f;
            tab.number_file++; 
        }
        d = readdir(dire);
    } 
    free(d);
    free(dire);
    return tab;    
}

DIR *open_directory(char *directory_name)
{
    DIR *d = opendir(directory_name);

    if(_is_null(d))
    {
        fprintf(stderr, "Cant open directory.\n");
        exit(EXIT_FAILURE);
    }

    return d;
}

void error(void *e, char *message)
{
    if(_is_null(e))
    {
        fprintf(stderr, "%s:(\n", message);
        exit(EXIT_FAILURE);
    }
}

void _free_file(File f)
{
    error(f.name, "Cant free file sequence");
    free(f.name);
}

void free_tab_file(Tab_File tab_f)
{
    error(tab_f.file, "Cant free tab file");
    for(int i = 0; i < tab_f.number_file; i++)
        _free_file(tab_f.file[i]);
    
    free(tab_f.file);
}

void count_nb_occurence_char(FILE *file, char *name_file_result)
{
    Char_tree *t = creat_tree();
    char c = getc(file);
    while(c != EOF)
    {
        if(isalpha(c))
            t = add_char(t, c);
        c = getc(file);
    }
    
    char buffer[255] = {0};
    if( sprintf(buffer, "result_count/%s", name_file_result) < 0)
    {
        perror("sprintf()");
        return;
    }

    FILE *f = open_file(buffer, "a");
    set_result_tree(t, f);

    close_file(f);
    free_tree(t);
}

void count_nb_occurence_separator(FILE *file, char *name_file_result)
{
    Char_tree *t = creat_tree();
    char c = getc(file);
    while(c != EOF)
    {
        if(c == '.' || c == ';' || c == '!' || c == '?' || c == ':' || c == ',')
            t = add_char(t, c);
        c = getc(file);
    }
    char buffer[255] = {0};
    if( sprintf(buffer, "result_count/%s", name_file_result) < 0)
    {
        perror("sprintf()");
        return;
    }

    FILE *f = open_file(buffer, "a");

    set_result_tree(t, f);

    close_file(f);
    free_tree(t);
}

void count_nb_occurence_word(FILE *file, char *name_file_result)
{
    Word_tree *t = creat_word_tree();
    char c = getc(file), buffer_read[SIZE_WORD] = {0};
    int i = 0;
    while(c != EOF)
    {
        if(isalnum(c) || isalpha(c))
            buffer_read[i++] = c;
        else 
        {
            t = add_word(t, buffer_read);
            for(int j = 0; j < SIZE_WORD; buffer_read[j++] = 0);
            i = 0;
        }
        c = getc(file);
    }
    char buffer[255] = {0};
    if( sprintf(buffer, "result_count/%s", name_file_result) < 0)
    {
        perror("sprintf()");
        return;
    }

    FILE *f = open_file(buffer, "a");
    set_result_word_tree(t, f);

    close_file(f);
    free_word_tree(t);
}