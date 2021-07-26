#include <iostream>

#include "GUIFramework.h"

using namespace std;

int main(int argc, char** argv)
{
	try
	{
		gui_framework::GUIFramework& instance = gui_framework::GUIFramework::get();


	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
