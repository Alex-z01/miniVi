#include "Undo.h"

void Undo::setChar(char C) {
	deletedC = C;
}
void Undo::setString(string S) {
	deletedS = S;
}
void Undo::setLastPos(Position LP) {
	lastPos = LP;
}
void Undo::setLastCMD(char LCMD) {
	lastCMD = LCMD;
}
char Undo::getC() {
	return deletedC;
}
char Undo::getCMD() {
	return lastCMD;
}
string Undo::getS() {
	return deletedS;
}
Position Undo::getPos() {
	return lastPos;
}