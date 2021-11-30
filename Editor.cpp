#include <iostream>
#include <conio.h>
#include <fstream>
#include <Windows.h>
#include "Editor.h"
#include "Position.h"
#include "quicksort.cpp"

using namespace std;

//Initialize cursor 
void CursorInit(Position coordinate) {

	HANDLE hStdout;
	COORD coord;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	coord.X = coordinate.getX();

	coord.Y = coordinate.getY();

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Change color of text
void colorText(string value) {

	COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	FlushConsoleInputBuffer(hConsole);

	if(value == "white")
		SetConsoleTextAttribute(hConsole, 7);
	if (value == "blue")
		SetConsoleTextAttribute(hConsole, 9);

}

//Search array 
int binarySearch(const string anArray[], int first, int last, string target)
{
	int index;
	if (first > last)
		index = -1; // target not in original array
	else
	{
		// If target is in anArray, anArray[first] <= target <= anArray[last]
		int mid = first + (last - first) / 2;
		if (target == anArray[mid])
			index = mid; // target found at anArray[mid]
		else if (target < anArray[mid])
			// Point X
			index = binarySearch(anArray, first, mid - 1, target);
		else
			// Point Y
			index = binarySearch(anArray, mid + 1, last, target);
	}  // end if

	return index;
}

//Defualt Constructor
Editor::Editor()
{
	ReadKeywords();
}

//Constructor with given file
Editor::Editor(string file)
{
	ReadKeywords();

	fileName = file;
	myFile.open(fileName);

	int counter = 1;

	while (!myFile.eof())
	{
		getline(myFile, tempText);
		cout << tempText;
		allText.insert(counter, tempText);
		counter++;
	}

	myFile.close();
}

//Read keywords from file into array and sort array
void Editor::ReadKeywords()
{
	fstream file;
	file.open("keywords.txt");

	int counter = 0;
	while (!file.eof())
	{
		getline(file, tempText);
		keywords[counter] = tempText;
		counter++;
	}

	quickSort(keywords, 0, 60);
}

//Display the lines from allText LinkedList
void Editor::DisplayLines()
{	
	int position;
	string nextLine, nextWord, line;

	for (position = 1; position <= allText.getLength(); position++)
	{
		nextLine = allText.getEntry(position);

		int i = 0;
		while (i < nextLine.length())
		{
			string word; 
			if (isalpha(nextLine[i])) {
				while (isalpha(nextLine[i]) || nextLine[i] == '_') {
					word += nextLine[i];
					i++;
				}
				if (binarySearch(keywords, 0, 60, word) != -1)  //found
				{
					colorText("blue");
				}
				else
				{
					colorText("white");
				}
				cout << word;
			}
			else {
				colorText("white");
				cout << nextLine[i];
				i++;
			}
		}
		cout << endl;
	}

	CursorInit(pos);
}

//Run loop, fetch in commands from input
void Editor::run()
{
	system("cls");
	DisplayLines();
	command = _getch();

	switch (command)
	{
	case 'x':
		DeleteChar();
		run();
		break;
	case 'q':
		command = _getch();
		switch (command)
		{
		case '!':
			pos.setCursorPos(0, allText.getLength());
			exit;
			break;
		default:
			if (Quit()) { break; }
			else { run(); break; }
			run();
			break;
		}
		break;
	case 'w':
		Save();
		run();
		break;
	case 'j': // Move down
		Move("DOWN");
		run();
		break;
	case 80: // Arrow down
		Move("DOWN");
		run();
		break;
	case 'k': // Move up
		Move("UP");
		run();
		break;
	case 72:  // Arrow up
		Move("UP");
		run();
		break;
	case 'h': // Move left
		Move("LEFT");
		run();
		break;
	case 75: // Arrow left
		Move("LEFT");
		run();
		break;
	case 'l': // Move right
		Move("RIGHT");
		run();
		break;
	case 77: // Arrow right
		Move("RIGHT");
		run();
		break;
	case 'u': //Undo
		undo();
		run();
		break;
	case ':':
		pos.moveCursor(0, allText.getLength());
		run();
		break;
	case 'd':
		command = _getch();
		switch (command)
		{
		case 'd':
			WriteUndo(' ', allText.getEntry(pos.getY() + 1));
			allText.remove(pos.getY() + 1);
			run();
			break;
		default:
			WriteChar(command);
			run();
			break;
		}
	default:
		run();
	}
}

//Move cursor
void Editor::Move(string direction)
{
	if (direction == "UP"){
		if (pos.getY() > 0)
		{
			pos.moveCursor(0, -1);
			if(pos.getX() > allText.getEntry(pos.getY() + 1).length())
				pos.setX(allText.getEntry(pos.getY() + 1).length());
		}
	}
	if (direction == "DOWN") {
		if (pos.getY() < allText.getLength() - 1)
		{
			pos.moveCursor(0, 1);
			if (pos.getX() > allText.getEntry(pos.getY() + 1).length())
				pos.setX(allText.getEntry(pos.getY() + 1).length());
		}
	}
	if (direction == "LEFT") {
		if (pos.getX() > 0)
		{
			pos.moveCursor(-1, 0);
		}
	}
	if (direction == "RIGHT") {
		if (pos.getX() < allText.getEntry(pos.getY() + 1).length())
		{
			pos.moveCursor(1, 0);
		}
	}
}

//Write char to allText LinkedList 
void Editor::WriteChar(char cmd)
{
	string cur = allText.getEntry(pos.getY() + 1);
	string L1, L2;
	for (int i = 0; i < pos.getX(); i++)
	{
		L1 += cur[i];
	}
	for (int i = pos.getX(); i < cur.length(); i++)
	{
		L2 += cur[i];
	}
	string newline = L1 + cmd + L2;
	allText.replace(pos.getY()+1, newline);
}

//Delete char from allText LinkedList
void Editor::DeleteChar()
{
	string cur = allText.getEntry(pos.getY()+1);
	string newline;
	for (int i = 0; i < cur.length(); i++)
	{
		if (i != pos.getX())
		{
			newline += cur[i];
		}
		else {
			WriteUndo(cur[i], "");
		}
	}
	allText.replace(pos.getY() + 1, newline);
	changes = true;
}

//Initlize new Undo object and update latest values then push to undos LinkedStack
void Editor::WriteUndo(char C, string S)
{
	lastAction.setChar(C); //Set last deleted char
	lastAction.setString(S); //Set last deleted line
	lastAction.setLastPos(pos); //Set last pos
	lastAction.setLastCMD(command); //Set last used command
	undos.push(lastAction);
}

//Undo
void Editor::undo()
{
	if (!undos.isEmpty()) {
		Undo checkLastAction = undos.peek();
		undos.pop();
		pos = checkLastAction.getPos();
		if (checkLastAction.getCMD() == 'x') {
			WriteChar(checkLastAction.getC());
		}
		if (checkLastAction.getCMD() == 'd') {
			allText.insert(pos.getY() + 1, checkLastAction.getS());
		}

	}
}

//Save
void Editor::Save()
{
	myFile.open(fileName, ofstream::out | ofstream::trunc);

	for (int i = 0; i < allText.getLength(); i++)
	{
		myFile << allText.getEntry(i + 1) << endl;
	}

	myFile.close();

}

//Quit, prompt save
bool Editor::Quit()
{
	string cond;
	pos.setCursorPos(0, allText.getLength());

	if (changes)
	{
		cout << "Do you want to quit without saving? y/n" << endl;
		cin >> cond;

		if (cond == "y")
		{
			return true;
		}
		else {
			pos.setCursorPos(0, 0);
			return false;
		}
	}
	else {
		pos.setCursorPos(0, allText.getLength());
		return true;
	}
	
}