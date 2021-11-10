#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <conio.h>
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

int main()
{
	Position pos(0, 0);
	Editor ed("input.txt");

	CursorInit(pos);

	ed.run();

	
}
