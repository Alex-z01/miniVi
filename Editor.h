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
	string fileName;
	char command;
	bool isRunning = true;
	LinkedList<char> allText;
	fstream myFile;
};

#endif // !EDITOR_H


