#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <string>
#include <list>
#include "Node.h"
#include "LinkedList.h"
#include "ListInterface.h"
#include "Position.h"

using namespace std;

class Editor
{
public:
	Editor();
	Editor(string fileName);
	void run();
	void DisplayLines();
	void CurrentLine();
	void WriteChar(char cmd);
	void DeleteChar();
	void Save();
	bool Quit();
private:
	string fileName, tempText;
	char command;
	bool isRunning = true;
	bool changes = false;
	LinkedList<string> allText;
	fstream myFile;
	Position pos;
};

#endif // !EDITOR_H


