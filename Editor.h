#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <string>
#include <list>
#include "Node.h"
#include "LinkedList.h"
#include "ListInterface.h"
#include "Position.h"
#include "LinkedStack.h"
#include "StackInterface.h"
#include "Undo.h"

using namespace std;

class Editor
{
public:
	Editor();
	Editor(char* inputFile, string keywordsFile);
	void run();
	void ReadKeywords(string file);
	void Move(string direction);
	void DisplayLines();
	void CurrentLine();
	void WriteChar(char cmd);
	void DeleteChar();
	void WriteUndo(char C, string S);
	void undo();
	void Save();
	bool Quit();
private:
	//Chars
	char command;
	//Strings
	string fileName, tempText;
	string keywords[61];
	//Bools
	bool isRunning = true;
	bool changes = false;
	//Custom Classes
	Undo lastAction;
	LinkedStack<Undo> undos;
	LinkedList<string> allText;
	Position pos;
	//Files
	fstream myFile;
};

#endif // !EDITOR_H


