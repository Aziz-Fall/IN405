run: main
	valgrind ./main 

main: main.o atlacan.o
	gcc main.o atlacan.o -O1 -o main -g 

main.o: main.c 
	gcc -O1 -c -g  main.c 

atlacan.o: atlacan.c atlacan.h
	gcc -O1 -c -g atlacan.c 
clean:
	rm -Rf *.o
	rm -f main 
	clear 