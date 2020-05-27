run: main.o report.o
	gcc main.o report.o -o a.out
main.o: main.c VAR.h
	gcc -c main.c
report.o: report.c VAR.h
	gcc -c report.c
