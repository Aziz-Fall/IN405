OPTION   	 = -g -Wall 
COUNT_CHAR   = count_char/count_char
COUNT_WORD   = count_word/count_word
FILE_MANAGER = file_manager/file_manager
COM_PROCESS  = communication_process/com_process 
CHECK_COM    = check_command/check_command

run: main 
	./main wpc w 2 234 files

main: main.o ${COUNT_CHAR}.o ${COUNT_WORD}.o ${FILE_MANAGER}.o ${COM_PROCESS}.o ${CHECK_COM}.o
	gcc *.o -o  main ${OPTION}

main.o: main.c 
	gcc -c -O1 main.c ${OPTION}

${COUNT_WORD}.o: ${COUNT_WORD}.c 
	gcc -c -O1 ${COUNT_WORD}.c ${OPTION}

${COUNT_CHAR}.o: ${COUNT_CHAR}.c 
	gcc -c -O1 ${COUNT_CHAR}.c ${OPTION}


${FILE_MANAGER}.o: ${FILE_MANAGER}.c 
	gcc -c -O1 ${FILE_MANAGER}.c ${OPTION}


${CHECK_COM}.o: ${CHECK_COM}.c 
	gcc -c -O1 ${CHECK_COM}.c ${OPTION}

${COM_PROCESS}.o: communication_process/com_process.c
	gcc -c -O1 communication_process/com_process.c ${OPTION}

clean:
	rm -fr main *.o 
	rm -r result_count/*
	clear 