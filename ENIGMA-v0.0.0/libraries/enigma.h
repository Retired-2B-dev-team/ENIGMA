// Library with some useful (I hope) stuff for implementing ENIGMA machine simulations
// 1/14/2022	<RETIRED-2B-DEV-TEAM>

/*
Example:

    - ALPHABET:

Letter indexes:  0. 1. 2. 3. 4.
                [A, B, C, D, F]

    - MACHINE'S FRAGMENT :

            Disk index:  0.     1.     2.
                         |      |      |
--------   /  0.   (A)->[3]-   [0]    [4]
|Letter|  |   1.    ^   [0] \  [4]    [1]
|index | <    2.    ^   [1]  \ [3] /--[3] => (D)
--------  |   3.    ^   [4]   -[2]/   [0]
		   \  4.    ^   [2]    [1]    [2]
                    ^    |      |      |
            input->>^    |      |      |
                        Disks represented
						  by 1D arrays
						  (connections)
*/

#include <algorithm>

#include "headquarters.h" // namespace: "hq"



namespace eng
{

	const int STD_ALPHA_LEN = 26; // length of the alphabet used by the machine
	const int STANDARD_DISKS_AMOUNT = 3;	 // amount of disks with letters, used in the machine
	const int IRREGULAR_LETTER = -1;

	class Disk
	{

	// private: // private attributes
	public:
		int* connections; // an array describing the disk construction
		int rotation;
		int size; // amount of letters on the single disk

	private: // private methods
		void __correct_rotation__()
		{
			while (rotation >= size)
			{
				rotation -= size;
			}
			while (rotation < 0)
			{
				rotation += size;
			}
		}

		int __normalize__(int __index)
		{
			// this function grab index and add rotation tiks to it, so signal can be passed to the right spot on the ring
			int output = rotation + __index;

			if (output >= size) // if index of out input is out of range of disk
			{
				output -= size;
			}

			return output;
		}

	public: // public methods
		// void load(std::string file_name)
		// {
		// 	// this function should load the disk's letter connections from file and initialize disk
		// }

		void init(int* __connections, int __disk_size)
		{
			// function that is used to prepare disk before usage
			rotation = 0;

			size = __disk_size;
			connections = new int[size];

			std::copy(__connections, __connections + size, connections);
		}

		void rotate(int __rotation_tiks)
		{
			// function used to rotate disk
			rotation += __rotation_tiks;
			__correct_rotation__();
		}

		int forward(int index)
		{
			// pass signal through disk
			return connections[__normalize__(index)];
		}

		void get_visual()
		{
			
			for (int i = 0; i < size; i++)
			{
				std::cout << forward(i) << ' ';
			}
		}
	};

	class Enigma
	{

	private: // private attributes
		char* alphabet; // ENIGMA machine's alphabet array
		int* characters_ascii_indexes; // array used to convert characters to numbers (under specific ASCII index, in this array there is a number that represent this character)

	public:
		Disk plugin_board;
		Disk* disks;
		Disk reflector; // reversing roller
		Disk* reversed_disks;
		int disks_amount; // current amount of disks

		int alphabet_length;

	private: // private methods
		char __number_to_char__(int number)
		{
			return alphabet[number];
		}

		int __char_to_number__(char character)
		{
			return characters_ascii_indexes[(int)character];
		}

		void __index_alphabet__(std::string __machine_alphabet)
		{
			// this function fills character_ascii_indexes with numbers that represent proper sign in ascii table (usually it will be just small fragment of this table, just indexes of letters that are used by machine)
			hq::clear_int_array(characters_ascii_indexes, 0, hq::ASCII_CHARS_AMOUNT, IRREGULAR_LETTER);

			for (int i = 0; i < __machine_alphabet.size(); i++)
			{
				alphabet[i] = __machine_alphabet[i];
				characters_ascii_indexes[(int)alphabet[i]] = i;
			}
		}

		Disk __create_reversed_disk__(Disk __starting_disk)
		{
			// function that generate reversed (index <-> values) version of specific disk (it's needed when signal is 'returning', after it reachs reflector)
			Disk reversed_disk;
			int* reversed_connections = new int[alphabet_length];

			//std::cout << '\t';
			for (int i = 0; i < alphabet_length; i++)
			{
				//std::cout << __starting_disk.connections[i] << ' ';
				reversed_connections[__starting_disk.connections[i]] = i;
				// reversed_disk.connections[__starting_disk.connections[i]] = i;
			}
			
			reversed_disk.init(reversed_connections, alphabet_length);
			
			return reversed_disk;
		}

		void __init_plugin_board__()
		{
			// function that prepares plug-in board without any connections between letters
			int* __connections = new int[alphabet_length];

			for (int i = 0; i < alphabet_length; i++)
			{
				__connections[i] = i;
			}
			
			plugin_board.init(__connections, alphabet_length);
		}

	public:	// public methods
		Enigma(std::string __machine_alphabet, int __max_disks_amount = STANDARD_DISKS_AMOUNT)
		{
			// function that is used to prepare machine before usage

			alphabet_length = __machine_alphabet.size();
			alphabet = new char[alphabet_length];
			characters_ascii_indexes = new int[hq::ASCII_CHARS_AMOUNT];

			__index_alphabet__(__machine_alphabet);

			disks_amount = 0;
			disks = new Disk[__max_disks_amount];
			reversed_disks = new Disk[__max_disks_amount];
			__init_plugin_board__();
		}

		void add_disk(int* __connections)
		{
			// this function is used to define first / default disks

			disks[disks_amount].init(__connections, alphabet_length);

			//disks[disks_amount].get_visual();

			reversed_disks[disks_amount] = __create_reversed_disk__(disks[disks_amount]);

			disks_amount++;
		}

		void plug_in(char x, char y)
		{
			// this is function that allows to make a connection on plug-in board between two letters
			plugin_board.connections[__char_to_number__(x)] = __char_to_number__(y);
			plugin_board.connections[__char_to_number__(y)] = __char_to_number__(x);
		}

		void plug_out(char x)
		{
			// this is function that allows to disconnect two letters on plug-in board
			int y = plugin_board.connections[__char_to_number__(x)];
			plugin_board.connections[__char_to_number__(x)] = __char_to_number__(x);
			plugin_board.connections[y] = y;
		}

		void change_disk(int disk_index, int* __connections)
		{
			// this function is used to change currently used disk (from the machine) to another one
			disks[disk_index].init(__connections, alphabet_length);
			reversed_disks[disk_index] = __create_reversed_disk__(disks[disk_index]);
		}

		void set_reflector(int* __connections)
		{
			// this function is used to mount reflector into machine
			reflector.init(__connections, alphabet_length);
		}

		void load_connections(std::string __file_name, int* __connections)
		{
			// this function is used to load array describing disk / reflector / plugin board from text file
			char letter;
			//__connections = new int[alphabet_length];
			std::fstream myfile;

			myfile.open(__file_name.c_str(), std::ios::in);
			for (int i = 0; i < alphabet_length; i++)
			{
				myfile >> letter;
				__connections[i] = __char_to_number__(letter);
				//std::cout << letter << ' ' << __connections[i] << ' ';
			}
			myfile.close();
			// add_disk(__connections);
		}
		
		std::string get_visual()
		{
			std::string output = "";
			
			for (int i = 0; i < disks_amount; i++)
			{
				for (int j = 0; j < alphabet_length; j++)
				{
					output += __number_to_char__(j);
					output += ": ";
					output += __number_to_char__(disks[i].forward(j));
					output += ", ";
					output += __number_to_char__(reversed_disks[i].forward(j));
					output += "; ";
				}
				output += "\n\n";
			}
			
			return output;
		}
		
		int transcribe(int __letter, int __disk_number, Disk* __disks)
		{
			 // this function changes input letter according to connections in the disk
			int output = __disks[__disk_number].forward(__letter);
			return output;
		}


		char encrypt_letter(char __letter) // this is the encryption mechanism, it goes throught all disks(foward and back) and outputs an encrypted letter
		{
			// this function take a letter on the input, goes through every part of the machine, and returns processed, encripted version of the input
			int output = __char_to_number__(__letter);

			if (output == IRREGULAR_LETTER)
			{
				return __letter;
			}
			else
			{
				output = plugin_board.forward(output);

				for (int i = 0; i < disks_amount; i++)
				{
					//std::cout << "checkpoint " << i << '.';
					output = transcribe(output, i, disks);
					//output = disks[i].forward(output);
				}

				output = reflector.forward(output);

				for (int i = disks_amount - 1; i >= 0; i--)
				{
					output = transcribe(output, i, reversed_disks);
				}

				output = plugin_board.forward(output);

				return __number_to_char__(output);
			}
		}

		std::string encrypt_message(std::string __message)
		{
			// this function goes through every letter in message and encrypt/decrypt it using encrypt_letter function
			std::string output = "";
			
			for (int i = 0; i < __message.size(); i++)
			{
				output += encrypt_letter(hq::capital(__message[i]));
			}

			return output;
		}
	};
}
