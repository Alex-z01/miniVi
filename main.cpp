#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Editor.h"

using namespace std;

int main(int argc, char* argv[])
{
	Editor ed(argv[1], "keywords.txt");

	ed.run();
}
