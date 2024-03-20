
# Specifiy the target
all: food_reader

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
food_reader: main.o Company.o Menu.o MenuItem.o Franchise.o
	g++ main.o Company.o Menu.o MenuItem.o Franchise.o -o food_reader

# Specify how the object files should be created from source files
main.o: main.cpp Company.h Menu.h
	g++ -c main.cpp

Company.o: Company.cpp Company.h Menu.h
	g++ -c Company.cpp 

Menu.o: Menu.cpp Menu.h
	g++ -c Menu.cpp

MenuItem.o: MenuItem.cpp MenuItem.h
	g++ -c MenuItem.cpp

Franchise.o: Franchise.cpp Franchise.h
	g++ -c Franchise.cpp
# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o food_reader