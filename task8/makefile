all: clean matrix_mult

flags = -std=gnu17 -O3 -march=native -Wall -Wextra -pedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now -flto -Og -g -fno-omit-frame-pointer

matrix_mult: matrix_mult.o
	gcc matrix_mult.o -o matrix_mult.out

matrix_mult.o: matrix_mult.c
	gcc -c $(flags) matrix_mult.c

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp *.out