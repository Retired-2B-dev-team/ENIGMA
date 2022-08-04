#include <iostream>
#include "libraries/enigma.h"

using namespace eng;

const std::string HELP_FILE_NAME = "help.info";
const std::string VERSION_FILE_NAME = "version.info";
const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";



int main(int argc, char** argv)
{
	
	std::vector<std::string>args = hq::cmd::separate_args(argc, argv);

	for (int i = 0; i < args.size(); i++)
	{
		std::cout << args[i] << '\t';
	}

	return 0;
}