all: clean sort

flags = -std=gnu17 -O3 -march=native -Wall -Wextra -pedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now -flto -Og -g -fno-omit-frame-pointer

sort: sort.o
	gcc sort.o -o sort.out

sort.o: sort.c
	gcc -c $(flags) sort.c

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp *.out