all: arbolito.bin

arbolito.bin: main.cpp selfLearnTree.o
	g++ main.cpp selfLearnTree.o -o arbolito.bin -Wextra -g

selfLearnTree.o: selfLearnTree.cpp selfLearnTree.hpp
	g++ selfLearnTree.cpp -c

clean: