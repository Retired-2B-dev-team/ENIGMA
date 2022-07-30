#include <iostream>
#include <string>
#include "libraries/enigma.h"

using namespace eng;

const std::string HELP_FILE_NAME = "";
const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::string read_file(std::string file_name)
{
	std::fstream file;
	std::string line = "";
	std::string text = "";
	
	file.open(file_name, std::ios::in);
	while (std::getline(file, line))
	{
		text += line + '\n';
	}
	file.close();

	return text;
}

void cmd(int argc, char** argv)
{
	for (int i = 0; i < argc; i++)
	{
		if (argv[i] == "--help" || argv[i] == "-?" || argv[i] == "-h")
		{
			std::cout << read_file(HELP_FILE_NAME);
		}
	}
}

int main(int argc, char** argv)
{
	Enigma enigma(ALPHABET);
	
	return 0;
}