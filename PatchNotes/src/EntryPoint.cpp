#include <iostream>

#include "pch.h"

#include "Initializer.h"

#pragma warning(disable: 28251)

using namespace std;

int wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		unique_ptr<gui_framework::WindowHolder> holder;

		Initializer::get().initialize(holder);

		holder->runMainLoop();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
