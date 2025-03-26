all: clean stat

flags = -std=c11 -O3 -march=native -Wall -Wextra -pedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now -flto -Og -g -fno-omit-frame-pointer

stat: stat.o
	gcc stat.o -o ./a.out

stat.o: stat.c
	gcc -c $(flags) stat.c

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp *.out