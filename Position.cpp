#include <iostream>
#include "Position.h"

Position::Position(){}

Position::Position(int x, int y)
{
	setCursorPos(x, y);
}

void Position::setCursorPos(int x, int y)
{
	coord.X = x;

	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Position::setX(int x)
{
	coord.X = x;
}

void Position::setY(int y)
{
	coord.Y = y;
}

int Position::getX()
{
	return coord.X;
}

int Position::getY()
{
	return coord.Y;
}