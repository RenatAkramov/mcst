all: clean sub

flags = -std=gnu17 -O3 -march=native -Wall -Wextra -pedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now -flto -Og -g -fno-omit-frame-pointer

sub: sub.o
	gcc sub.o -o sub.out

sub.o: sub.c
	gcc -c $(flags) sub.c

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp *.out