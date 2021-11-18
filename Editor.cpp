#include <iostream>
#include <conio.h>
#include <fstream>
#include <Windows.h>
#include "Editor.h"
#include "Position.h"

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

Editor::Editor()
{

}

Editor::Editor(string file)
{
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

void Editor::DisplayLines()
{	
	for (int i = 1; i <= allText.getLength(); i++)
	{	
		cout << allText.getEntry(i) << endl;
	}
	CursorInit(pos);
}

void Editor::run()
{
	system("cls");
	DisplayLines();
	command = _getch();

	switch (command)
	{
	case '\b':
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
		if (pos.getY() < allText.getLength()-1)
		{
			pos.moveCursor(0, 1);
		}
		run();
		break;
	case 'k': // Move up
		if (pos.getY() > 0)
		{
			pos.moveCursor(0, -1);
		}
		run();
		break;
	case 'h': // Move left
		if (pos.getX() > 0)
		{
			pos.moveCursor(-1, 0);
		}
		run();
		break;
	case 'l': // Move right
		if (pos.getX() < allText.getEntry(pos.getY()+1).length())
		{
			pos.moveCursor(1, 0);
		}
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
			allText.remove(pos.getY() + 1);
			run();
			break;
		default:
			run();
			break;
		}
	default:
		WriteChar(command);
		run();
	}
}

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
	}
	allText.replace(pos.getY() + 1, newline);
	changes = true;
}

void Editor::Save()
{
	myFile.open(fileName, ofstream::out | ofstream::trunc);

	for (int i = 0; i < allText.getLength(); i++)
	{
		myFile << allText.getEntry(i + 1) << endl;
	}

	myFile.close();

}

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