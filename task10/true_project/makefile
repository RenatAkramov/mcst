all: clean bul

flags =-std=gnu17 -O3 -march=native -Wall -Wextra -pedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now -flto -Og -g -fno-omit-frame-pointer -D_DEBUG
 
bul: main.o lexical_analysis.o syntax_analysis.o grafdump.o
	gcc main.o grafdump.o lexical_analysis.o syntax_analysis.o -o a.out

main.o: main.c
	gcc -c $(flags) main.c

lexical_analysis.o: lexical_analysis.c
	gcc -c $(flags) lexical_analysis.c

syntax_analysis.o: syntax_analysis.c
	gcc -c $(flags) syntax_analysis.c 

grafdump.o: grafdump.c
	gcc -c $(flags) grafdump.c 

clean:
	rm -rf *.o *.out 