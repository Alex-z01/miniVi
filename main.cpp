#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <conio.h>
#include "Editor.h"
#include "Position.h"

using namespace std;

int main()
{
	string text;
	Editor ed("input.txt");


	ed.run();
	
}
