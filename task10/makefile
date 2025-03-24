all: clean bul

flags = -std=c11 -O3 -march=native -Wall -Wextra -pedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now -flto -Og -g -fno-omit-frame-pointer

bul: bul_func.o grafdump.o read_tree.o
	gcc bul_func.o grafdump.o read_tree.o -o ./a.out

bul_func.o: bul_func.c
	gcc -c $(flags) bul_func.c

grafdump.o: grafdump.c
	gcc -c $(flags) grafdump.c

read_tree.o: read_tree.c
	gcc -c $(flags) read_tree.c

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp *.out
