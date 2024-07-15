main: 
	gcc -Wall -Wextra -Wpedantic -std=c17 -march=haswell -o exe main.c lexer.c

clean: 
	rm -f exe *.o