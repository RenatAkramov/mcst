all: clean err

flags = -std=gnu17 -O3 -march=native -Wall -Wextra -pedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now -flto -Og -g -fno-omit-frame-pointer

err: err.o
	gcc err.o -o ./a.out

err.o: err.c
	gcc -c $(flags) err.c

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp *.out