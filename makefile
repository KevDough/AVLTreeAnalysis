all: launch test

valgrind:
	valgrind -v --leak-check=full ./test.exe test.txt

launch: main.o Heap.o AVLTree.o Launch.o User.o
	g++ -std=c++11 -g User.o Heap.o AVLTree.o Launch.o main.o -o launch.exe

test: mainTest.o Heap.o AVLTree.o Launch.o User.o
	g++ -std=c++11 -g User.o Heap.o AVLTree.o Launch.o mainTest.o -o test.exe

mainTest.o: mainTest.cpp
	g++ -c -g mainTest.cpp

main.o: main.cpp
	g++ -c -g main.cpp
Heap.o: Heap.cpp Heap.h
	g++ -c -g Heap.cpp
AVLTree.o: AVLTree.cpp AVLTree.h
	g++ -c -g AVLTree.cpp
Launch.o: Launch.cpp Launch.h
	g++ -c -g Launch.cpp
User.o: User.cpp User.h
	g++ -c -g User.cpp


clean:
	rm -f *.o *.exe