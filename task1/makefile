all: clean par_sort

flags = -std=gnu17 -O3 -pthread -march=native -Wall -Wextra -pedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now -flto -Og -g -fno-omit-frame-pointer

par_sort: par_sort.o
	gcc par_sort.o -o par_sort.out

par_sort.o: par_sort.c
	gcc -c $(flags) par_sort.c

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp *.out