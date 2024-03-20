# Specifiy the target
all: dll

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
dll: main.o DLL.o
	g++ main.o DLL.o -o dll

# Specify how the object files should be created from source files
main.o: main.cpp DLL.h
	g++ -c main.cpp

DLL.o: DLL.cpp DLL.h
	g++ -c DLL.cpp

clean:
	rm -f *.o dll