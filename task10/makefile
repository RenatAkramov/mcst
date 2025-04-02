all: clean diff

flags =-std=gnu17 -O3 -march=native -Wall -Wextra -pedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now -flto -Og -g -fno-omit-frame-pointer
 
diff: differentiator.o grafdump.o read_tree.o lec.o main.o simplifare.o print_Latex.o
	g++ differentiator.o grafdump.o read_tree.o lec.o print_Latex.o main.o simplifare.o -o ./a.out

differentiator.o: differentiator.cpp
	g++ -c $(flags) differentiator.cpp

grafdump.o: grafdump.cpp
	g++ -c $(flags) grafdump.cpp

read_tree.o: read_tree.cpp
	g++ -c $(flags) read_tree.cpp

lec.o: lec.cpp
	g++ -c $(flags) lec.cpp

main.o: main.cpp
	g++ -c $(flags) main.cpp

simplifare.o: simplifare.cpp
	g++ -c $(flags) simplifare.cpp

print_Latex.o: print_Latex.cpp
	g++ -c $(flags) print_Latex.cpp

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp *.out *.aux *.log *.fls *.pdf *.gz *.fdb_latexmk *.dot *.png *.tex
