#include <iostream>
#include <conio.h>
#include <fstream>
#include <Windows.h>
#include "Editor.h"
#include "Position.h"

using namespace std;

Editor::Editor()
{

}

Editor::Editor(string file)
{
	fileName = file;
	string tempText;
	myFile.open(fileName);

	while (!myFile.eof())
	{
		getline(myFile, tempText);
		for (int i = 0; i <= tempText.length(); i++)
		{
			allText.insert(i+1, tempText[i]);
		}
		allText.insert(allText.getLength(), '\n');
	}

	myFile.close();
}

void Editor::DisplayLines()
{	
	for (int i = 1; i <= allText.getLength(); i++)
	{	
		cout << allText.getEntry(i);
	}
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
	case ':':
		// moves cursor to bottom
		cout << "Command found" << endl;
		run();
		break;
	case 'q':
		if (Quit()) { break; }
		else { run(); break; }
		break;
	case 'w':
		Save();
		run();
		break;
	default:
		WriteChar(command);
		run();
	}
}

void Editor::WriteChar(char cmd)
{
	allText.insert(allText.getLength(), cmd);
}

void Editor::DeleteChar()
{
	allText.remove(allText.getLength());
}

void Editor::Save()
{
	myFile.open(fileName, ofstream::out | ofstream::trunc);

	for (int i = 0; i < allText.getLength(); i++)
	{
		myFile << allText.getEntry(i+1);
	}

	myFile.close();

	cout << "\nSaving..." << endl;
	Sleep(1500);
}

bool Editor::Quit()
{
	string cond;
	cout << "Do you want to quit without saving? y/n" << endl;
	cin >> cond;

	if (cond == "y")
	{
		return true;
	}
	else {
		return false;
	}
}