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

void cmd(int argc, char** argv, Enigma* enigma)
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
		else if (i < arguments.size() - 1) // if it's not last provided input/parameter
		{
			if (argument == "-f" || argument == "--file")
			{
				i++; // we now gonna read value of the parameter
				std::string input_text = hq::read_file(arguments[i]);
				std::cout << enigma->encrypt_message(input_text);
			}
			else if (argument == "-t" || argument == "--text")
			{
				i++; // we now gonna read value of the parameter
				std::string input_text = arguments[i];
				std::cout << enigma->encrypt_message(input_text);
			}
		}
		else if (argument == "-s" || argument == "--setings")
		{
			
		}
		else
		{
			std::cout << "#Incorrect command use!";
		}
	}
}

int main(int argc, char** argv)
{
	// machine declaration:
	Enigma enigma(ALPHABET);
	// disks' connections:
	int BETA[STD_ALPHA_LEN];	enigma.load_connections(DISKS_PATH + "beta.rtr",	BETA);
	int GAMMA[STD_ALPHA_LEN];	enigma.load_connections(DISKS_PATH + "gamma.rtr",	GAMMA);
	int I[STD_ALPHA_LEN];		enigma.load_connections(DISKS_PATH + "I.rtr",		I);
	int II[STD_ALPHA_LEN];		enigma.load_connections(DISKS_PATH + "II.rtr",		II);
	int III[STD_ALPHA_LEN];		enigma.load_connections(DISKS_PATH + "III.rtr",		III);
	int IV[STD_ALPHA_LEN];		enigma.load_connections(DISKS_PATH + "IV.rtr",		IV);
	int V[STD_ALPHA_LEN];		enigma.load_connections(DISKS_PATH + "V.rtr",		V);
	int VI[STD_ALPHA_LEN];		enigma.load_connections(DISKS_PATH + "VI.rtr",		VI);
	int VII[STD_ALPHA_LEN];		enigma.load_connections(DISKS_PATH + "VII.rtr",		VII);
	int VIII[STD_ALPHA_LEN];	enigma.load_connections(DISKS_PATH + "VIII.rtr",	VIII);
	// reflectors' connections:
	int B[STD_ALPHA_LEN];		enigma.load_connections(REFLECTORS_PATH + "B.rtr", B);
	int C[STD_ALPHA_LEN];		enigma.load_connections(REFLECTORS_PATH + "C.rtr", C);

	// TEST / EXAMPLE set:
	enigma.add_disk(I);
	enigma.add_disk(II);
	enigma.add_disk(III);

	enigma.set_reflector(B);
	cmd(argc, argv, &enigma);

	// enigma.plug_in('A', 'B');

	// std::cout << enigma.get_visual();

	// std::cout << enigma.encrypt_letter('A');
	// std::cout << enigma.encrypt_letter('F');
	// std::cout << enigma.encrypt_letter('B');
	
	return 0;
}