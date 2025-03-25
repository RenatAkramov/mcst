all: clean par

flags = -std=c11 -O3 -march=native -Wall -Wextra -pedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now -flto -Og -g -fno-omit-frame-pointer

par: par.o
	gcc par.o -o ./a.out

par.o: par.c
	gcc -c $(flags) par.c

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp *.out