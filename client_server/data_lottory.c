#include "data_lottory.h"

FILE *open_file(char *name_file)
{
    FILE *f = fopen(name_file, "r");
    if(!f)
    {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    return f;
}
int get_match_number(FILE *f)
{
    rewind(f);
    char c = fgetc(f);
    return atoi(&c);
}

void get_num_lottory(FILE *f, int match_number, int a_num[])
{
    rewind(f);
    fgetc(f);
    for(int i = 0; i < match_number; i++)
        if( fscanf(f, "%d", (a_num + i)) == EOF )
          return;                                   
}

int get_match_gain(FILE *f, int match_number, int nb )
{
    rewind(f);
    int i, gain = 0;
    for( i = 0; i < 2; i++)
    {
        char buffer[255] = {0};
        if( !fgets(buffer, BUFFER, f) )
            return -1;
    }

    while( i < nb )
    {
        int tmp = 0, tmp_gain = 0;;
        if( fscanf(f, "%d %d", &tmp, &tmp_gain) == EOF)
            return -1;
        if( tmp == match_number)
        {
            gain = tmp_gain;
            break;
        }
    }

    return gain;
}

int is_client_win(int num_client[], int a_num[], int size)
{
   int i = 0, win = 1;
   while(win && i < size)
   {
       win = (num_client[i] ==  a_num[i]) ? 1 : 0;
       i++;
   }

    return win;
}

int check_match_number(int num_client[], int a_num[], int size)
{
    int c = 0;
    for(int i = 0; i < size; i++)
        if( num_client[i] == a_num[i]) c++;
    
    return c;
}

