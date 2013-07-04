#include "selfLearnTree.hpp"

#include <string>
#include <cstdlib>
#include <fstream>
#include <stack>

#define L_MASK 1
#define R_MASK 2

const string LittleArbolito::filename = "adivinator.data";

using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ios;
using std::string;
using std::ostream;
using std::stack;

extern LittleArbolito *arbol;


LittleArbolito::LittleArbolito(string val, LittleArbolito *l, LittleArbolito *r) 
								: value(val), left(l), right(r){
									grado = (left != NULL ? 1 : 0 ) + (right != NULL ? 2 : 0 );

									cout << "Nuevo Arbol" << endl;
								}

LittleArbolito::~LittleArbolito(){
	cout << "Hasta la vista" << endl;
}

string LittleArbolito::playDaGame(LittleArbolito *rootElement){
	bool response = false, otherResponses = false;

	while(rootElement != NULL && rootElement->isQuestion()){
		cout << "Pregunta: " << endl;
		cout << rootElement->getValue() << endl << "Si (1) o No (0) ? " << endl << ">> ";

		cin >> response;
		cin.ignore();

		rootElement = (response ? rootElement->getRightNode() : rootElement->getLeftNode());
	}

	if (rootElement != NULL){
		cout << "Estabas pensando en: " << rootElement->getValue() << "?"
													<< endl << "1 = Si / 0 = No >> ";

		cin >> otherResponses;
		cin.ignore();

		if (otherResponses){
			cout << "A hueso!!! Soy la onda!!! x3" << endl;
		}

		else{ // Fallo la aproximacion, solicitar pregunta y respuesta
			string newAnswer, newQuestion;

			cout << "Ayudame a mejorar!!!\n\nEn que estabas pensado?" << endl << ">> ";
			getline(cin, newAnswer);

			cout << "Dame una pregunta de tipo Si/No  Verdadero/Falso para identificarlo" << endl << ">> ";
			getline(cin, newQuestion);

			cout << "Y la respuesta a tu pregunta para llegar a la respuesta es:" << endl
				<< "1 = Si / 0 = No >> ";

			cin >> otherResponses;
			cin.ignore();

			this->addQuestion(rootElement, newAnswer, newQuestion, !response, otherResponses);

		}

	}

	/*

	else{ // Elemento desconocido, preguntar y agregar
		string newAnswer;

		cout << "Oops! Al parecer no conozco aún en que estas pensando" << endl;
		cout << "Podrias contarme??? :D (Hazlo! @.@)" << endl << ">> ";

		getline(cin, newAnswer);

		this->addAnswer(rootElement, newAnswer);

	}

	*/

	return string("OK");

}

bool LittleArbolito::isQuestion(){
	return (this->getLeftNode() != NULL || this->getRightNode() != NULL);
}

string LittleArbolito::getValue() const{
	return this->value;
}

void LittleArbolito::addQuestion(LittleArbolito *&rootElement, string nValue, string nQuestion,
									bool comesFromLeft, bool goesLeft){


	LittleArbolito *newAnswer = new LittleArbolito(nValue);
	LittleArbolito *movingAnswer = new LittleArbolito(rootElement->value);

	rootElement->value = nQuestion;

	rootElement->setLeftNode(!goesLeft ? newAnswer :  movingAnswer);
	rootElement->setRightNode(goesLeft ? newAnswer :  movingAnswer);
	
	return;
}

void LittleArbolito::addAnswer(LittleArbolito *&parent, string newAnswer){
	bool goesLeft = (parent->getLeftNode() == NULL);
	
	LittleArbolito *newAns = new LittleArbolito(newAnswer);

	(goesLeft ? parent->setLeftNode(newAns) : parent->setRightNode(newAns));

	return;
}


void LittleArbolito::loadTree(){
	fstream file;
	string reg;
	LittleArbolito *arbol;

	stack<LittleArbolito*> stackedTree;

	int hasLeft, hasRight;
	char buffer[256 + 1] = {0};

	file.open(LittleArbolito::filename.c_str(), ios::in);

	if (file.good()){
		while(!file.eof()){
			getline(file, reg);

			if (reg.length() < 2){
				break;
			}

			cout << reg << endl;

			sscanf(reg.c_str(), "%[^|]|%i|%i\n", &buffer, &hasLeft, &hasRight);

			arbol = new LittleArbolito(string(buffer),
				(LittleArbolito*)long(hasLeft), (LittleArbolito*)long(hasRight));

			stackedTree.push(arbol);

			if (! arbol->isQuestion()){
				stackedTree.pop();

				if (bool(stackedTree.top()->grado & L_MASK)){
					stackedTree.top()->setLeftNode(arbol);
					stackedTree.top()->grado -= L_MASK;
					
				} else if (bool(stackedTree.top()->grado & R_MASK)){
					// Solo para estar seguros D:
					stackedTree.top()->setRightNode(arbol);
					stackedTree.top()->grado -= R_MASK;
				}

				while (stackedTree.top()->grado == 0){ // Resolvemos los nuevos subarboles
					arbol = stackedTree.top();
					stackedTree.pop();

					if (stackedTree.empty()){
						this->value = arbol->value;
						this->setLeftNode(arbol->getLeftNode());
						this->setRightNode(arbol->getRightNode());

						break;
					}

					if (bool(stackedTree.top()->grado & L_MASK)){
						stackedTree.top()->setLeftNode(arbol);
						stackedTree.top()->grado -= L_MASK;
					
					} else if (bool(stackedTree.top()->grado & R_MASK)){
						// Solo para estar seguros D:
						stackedTree.top()->setRightNode(arbol);
						stackedTree.top()->grado -= R_MASK;
					}
				}

			}

			//cout << stackedTree << endl;

		}

	} else{ // if file.noGood() ? xD
		//Inicializame!
		string resp;
		cout << "Dame un valor inicial!!! O.<" << endl << ">> ";
		getline(cin, resp);

		this->value = resp;
	}

	

	// Leer e insertar

	file.close();

	return;
}

void LittleArbolito::saveTree(){
	fstream file;

	file.open(LittleArbolito::filename.c_str(), ios::out);

	// En preorden

	writeTree(file, this);
}

LittleArbolito *LittleArbolito::getLeftNode(){
	return left;
}

LittleArbolito *LittleArbolito::getRightNode(){
	return right;
}

void LittleArbolito::setLeftNode(LittleArbolito* left){
	this->left = left;
}

void LittleArbolito::setRightNode(LittleArbolito* right){
	this->right = right;
}

ostream& operator<< (ostream &stream, LittleArbolito &arbolito){

	stream << arbolito.value << "|" << (arbolito.getLeftNode() ? 1: 0)
			<< "|" << (arbolito.getRightNode() ? 1 : 0);

	return stream;
}

void cleanup(LittleArbolito **arbol){
	if (*arbol){
		LittleArbolito *var = (*arbol)->getLeftNode();

		cleanup(&var);

		var = (*arbol)->getRightNode();

		cleanup(&var);
		delete *arbol;
	}
}

void writeTree(ostream &stream, LittleArbolito *arbolito){

	if (arbolito){
		stream << (*arbolito) << endl;
		writeTree(stream, arbolito->getLeftNode());
		writeTree(stream, arbolito->getRightNode());
	}
}

void manage_interrupt(int signum){
   std::cout << "Cachame esta!!! x3" << endl;

   arbol->saveTree();

   exit(signum);
}
