#include <iostream>
#include <string>
#include "common.h"

int wmain(int argc, wchar_t* args[])
{
	const auto commandline{ stdCommandline(argc, args) };
	std::wcout << "writing commandline: " << std::endl;
	for (size_t i = 0; i < commandline.size(); i++)
	{
		std::wcout << concat(i, ") is ", commandline[i]) << std::endl;
	}
}