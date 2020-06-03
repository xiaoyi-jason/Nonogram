all: main

main: main.o table.o
	g++ main.o table.o -o main

main.o: main.cpp table.h
	g++ -c main.cpp -o main.o

table.o: table.cpp table.h
	g++ -c table.cpp -o table.o

clean:
	rm *.o main