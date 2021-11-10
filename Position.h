#ifndef POSITION_H
#define POSITION_H

#include <Windows.h>

class Position
{
public:
	Position();
	Position(int x, int y);
	void setCursorPos(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
private:
	COORD coord;
};

#endif // !POSITION_H
