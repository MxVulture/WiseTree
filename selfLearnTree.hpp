#ifndef _SELF_LEARN_TREE_H_
#define _SELF_LEARN_TREE_H_




#include <iostream>

using std::string;
using std::ostream;

class LittleArbolito{
	public:
	LittleArbolito(string val = "", LittleArbolito* l = NULL, LittleArbolito* r = NULL);
	~LittleArbolito();

	string playDaGame(LittleArbolito*);
	void loadTree();
	void saveTree();

	
	LittleArbolito *getLeftNode() ;
	LittleArbolito *getRightNode() ;

	void setLeftNode(LittleArbolito*);
	void setRightNode(LittleArbolito*);
	bool isQuestion() ;

	string getValue() const;


	friend ostream& operator<<(ostream&, LittleArbolito&);

	int grado;
	string value;

	private:
	const static string filename;
	
	class LittleArbolito *left, *right;
	void addQuestion(LittleArbolito*&, string, string, bool, bool);
	void addAnswer(LittleArbolito *&, string);

};


void manage_interrupt(int);
void writeTree(ostream&, LittleArbolito*);
void cleanup( LittleArbolito **arbol);

#endif