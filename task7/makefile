all: clean par_copy

flags = -std=gnu17 -O3 -pthread -march=native -Wall -Wextra -pedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now -flto -Og -g -fno-omit-frame-pointer

par_copy: par_copy.o
	gcc par_copy.o -o par_copy.out

par_copy.o: par_copy.c
	gcc -c $(flags) par_copy.c

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp *.out