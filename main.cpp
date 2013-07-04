#include <iostream>
#include <string>
#include <csignal>

#include "selfLearnTree.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

LittleArbolito *arbol;


int main(int argc, char const *argv[])
{
	arbol = new LittleArbolito();
	//arbol->loadTree();

	signal(SIGINT, manage_interrupt);

	cout << "Bienvenido! :D" << endl;

	cout << "Te haremos algunas preguntas para ver en que estas pensando!" << endl;

	cout << "Presiona Enter cuando estes listo! D:" << endl;

	cin.get();

//	while(true);

	arbol->loadTree();

	while(true)

		arbol->playDaGame(arbol);

//	cleanup(&arbol);

//	6 cafe y rosa

	return 0;
}