#include <iostream>
#include "libraries/enigma.h" // eng namespace

using namespace eng; // Enigma stuff namespace

// constants:
const std::string DISKS_PATH = "disks";
const std::string HELP_FILE_NAME = "help.info";
const std::string VERSION_FILE_NAME = "version.info";
const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// structures / classes:



// functions:

void cmd(int argc, char** argv)
{
	std::vector<std::string> arguments = hq::cmd::separate_args(argc, argv);
	std::string argument;
	
	for (int i = 0; i < arguments.size(); i++)
	{
		argument = arguments[i];

		if (argument == "-h" || argument == "--help")
		{
			std::cout << hq::read_file(HELP_FILE_NAME);
		}
		else if (argument == "-v" || argument == "--version")
		{
			std::cout << hq::read_file(VERSION_FILE_NAME);
		}
		else if (argument == "-f" || argument == "--file")
		{
			
		}
		else if (argument == "-t" || argument == "--text")
		{
			
		}
	}
}

int main(int argc, char** argv)
{
	// machine declaration:
	Enigma enigma(ALPHABET);
	// disks' connections:
	int* BETA;	enigma.load_connections(DISKS_PATH + "/beta.rtr",	BETA);
	int* GAMMA;	enigma.load_connections(DISKS_PATH + "/gamma.rtr",	GAMMA);
	int* I;		enigma.load_connections(DISKS_PATH + "/I.rtr",		I);
	int* II;	enigma.load_connections(DISKS_PATH + "/II.rtr",		II);
	int* III;	enigma.load_connections(DISKS_PATH + "/III.rtr",	III);
	int* IV;	enigma.load_connections(DISKS_PATH + "/IV.rtr",		IV);
	int* V;		enigma.load_connections(DISKS_PATH + "/V.rtr",		V);
	int* VI;	enigma.load_connections(DISKS_PATH + "/VI.rtr",		VI);
	int* VII;	enigma.load_connections(DISKS_PATH + "/VII.rtr",	VII);
	int* VIII;	enigma.load_connections(DISKS_PATH + "/VIII.rtr",	VIII);

	return 0;
}