run: test_lexc
	./test_lexc

test_lexc: test_lexc.o lexc.o 
	gcc *.o -o test_lexc -g -Wall 

lexc.o: lexc.c lexc.h 
	gcc -c lexc.c -g -Wall;

test_lexc.o: test_lexc.c lexc.h 
	gcc -c test_lexc.c -g -Wall;

run_with_valgrind: 
	valgrind ./test_lexc 	
clean:
	rm -r *.o 
	rm -r test_lexc 
	clear 