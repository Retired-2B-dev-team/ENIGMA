#include <iostream>
#include "libraries/enigma.h"

using namespace eng;

const std::string HELP_FILE_NAME = "help.info";
const std::string VERSION_FILE_NAME = "version.info";
const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int main(int argc, char** argv)
{
	std::string argument;
	std::string cryptogram_file_name;
	
	// command handling
	if (argc > 1)
	{
		argument = std::string(argv[1]);

		if (argument == "--help" || argument == "-?" || argument == "-h")
		{
			std::cout << hq::read_file(HELP_FILE_NAME);
		}
		else if (argument == "--version" || argument == "-v")
		{
			std::cout << hq::read_file(VERSION_FILE_NAME);
		}
		else if (argument == "-f")
		{
			if (argc > 2)
			{
				cryptogram_file_name = std::string(argv[2]);
			}
		}
	}
	
	
	return 0;
}