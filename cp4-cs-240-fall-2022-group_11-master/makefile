all: main

main: main.o User.o Maxheap.o
	g++ main.o User.o Maxheap.o -o main

main.o: main.cpp User.h Maxheap.h
	g++ -c main.cpp

User.o: User.cpp User.h
	g++ -c User.cpp

Maxheap.o: Maxheap.cpp Maxheap.h
	g++ -c Maxheap.cpp

clean:
	rm -f *.o main