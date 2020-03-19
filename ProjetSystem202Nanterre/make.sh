#!/bin/sh

MAIN='main'
MAIN_C='main.c'
OPTION='-O1 -g -Wall' 
COUNT_CHAR_C='count_char/count_char.c'
COUNT_WORD_C='count_word/count_word.c'
COM_PROCESS_C='communication_process/com_process.c' 
FILE_MANAGER_C='file_manager/file_manager.c'
CHECK_COMMAND_C='check_command/check_command.c'

if [ $# -eq 5 ];
then
    $CC $COUNT_CHAR_C $COUNT_WORD_C $FILE_MANAGER_C $COM_PROCESS_C $MAIN_C -o $MAIN  $OPTION
    ./$MAIN $1 $2 $3 $4 $5  
else
    echo "less arguments :|"
fi 



