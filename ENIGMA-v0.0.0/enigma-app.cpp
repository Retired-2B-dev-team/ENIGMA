#include <iostream>
#include "libraries/enigma.h" // eng namespace

using namespace eng; // Enigma stuff namespace

// constants:
const std::string DISKS_PATH = "disks/";
const std::string REFLECTORS_PATH = "reflectors/";
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
		else if (argument == "-s" || argument == "--setings")
		{
			
		}
	}
}

int main(int argc, char** argv)
{
	// machine declaration:
	Enigma enigma(ALPHABET);
	// disks' connections:
	int BETA[eng::STD_ALPHA_LEN];;	enigma.load_connections(DISKS_PATH + "beta.rtr",	BETA);
	int GAMMA[eng::STD_ALPHA_LEN];;	enigma.load_connections(DISKS_PATH + "gamma.rtr",	GAMMA);
	int I[eng::STD_ALPHA_LEN];		enigma.load_connections(DISKS_PATH + "I.rtr",		I);
	int II[eng::STD_ALPHA_LEN];;	enigma.load_connections(DISKS_PATH + "II.rtr",		II);
	int III[eng::STD_ALPHA_LEN];;	enigma.load_connections(DISKS_PATH + "III.rtr",		III);
	int IV[eng::STD_ALPHA_LEN];;	enigma.load_connections(DISKS_PATH + "IV.rtr",		IV);
	int V[eng::STD_ALPHA_LEN];;		enigma.load_connections(DISKS_PATH + "V.rtr",		V);
	int VI[eng::STD_ALPHA_LEN];;	enigma.load_connections(DISKS_PATH + "VI.rtr",		VI);
	int VII[eng::STD_ALPHA_LEN];;	enigma.load_connections(DISKS_PATH + "VII.rtr",		VII);
	int VIII[eng::STD_ALPHA_LEN];;	enigma.load_connections(DISKS_PATH + "VIII.rtr",	VIII);

	int B[eng::STD_ALPHA_LEN];;		enigma.load_connections(REFLECTORS_PATH + "B.rtr", B);
	int C[eng::STD_ALPHA_LEN];;		enigma.load_connections(REFLECTORS_PATH + "C.rtr", C);

	// for (int i = 0; i < 26; i++)
	// {
	// 	std::cout << I[i] << ' ';
	// }

	enigma.add_disk(I);
	enigma.add_disk(II);
	enigma.add_disk(III);

	enigma.set_reflector(B);


	std::cout << enigma.get_visual();

	std::cout << enigma.encrypt('A');
	std::cout << enigma.encrypt('N');
	
	return 0;
}