#ifndef UNDO_H
#define UNDO_H

#include <string>
#include "Position.h"

using namespace std;

class Undo {
public:
	void setChar(char C);
	void setString(string S);
	void setLastPos(Position LP);
	void setLastCMD(char LCMD);
	char getC();
	char getCMD();
	string getS();
	Position getPos();
private:
	char deletedC;
	string deletedS;
	Position lastPos;
	char lastCMD;
};

#endif