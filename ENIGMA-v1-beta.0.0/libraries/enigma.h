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
	const int EMPTY_NOTCH = -2;
	const char COMMENT_CHAR = '#';

	class Disk
	{

	// private: // private attributes
	public:
		int* connections; // an array describing the disk construction
		int rotation;
		int size; // amount of letters on the single disk
		int notch;
		int notch_second;

	private: // private methods
		// void __correct_rotation__()
		// {
		// 	while (Disk::rotation >= Disk::size)
		// 	{
		// 		Disk::rotation -= Disk::size;
		// 	}
		// 	while (Disk::rotation < 0)
		// 	{
		// 		Disk::rotation += Disk::size;
		// 	}
		// }

	public: // public methods
		// void load(std::string file_name)
		// {
		// 	// this function should load the disk's letter connections from file and initialize disk
		// }

		void init(int* connections, int disk_size, int notch = EMPTY_NOTCH, int notch_second = EMPTY_NOTCH, int rotation = 0)
		{
			// function that is used to prepare disk before usage
			Disk::notch = notch;
			Disk::notch_second = notch_second;
			Disk::rotation = rotation;

			Disk::size = disk_size;
			Disk::connections = new int[size];

			std::copy(connections, connections + size, Disk::connections);
		}

		void rotate(int rotation_tiks)
		{
			// function used to rotate disk
			Disk::rotation += rotation_tiks;
			rotation = hq::normalize(Disk::rotation, Disk::size);
		}

		int forward(int index)
		{
			// pass signal through disk
			index = hq::normalize(index + Disk::rotation, Disk::size);
			return hq::normalize(Disk::connections[index] - Disk::rotation, Disk::size);
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
			return Enigma::alphabet[number];
		}

		int __char_to_number__(char character)
		{
			return Enigma::characters_ascii_indexes[(int)character];
		}

		void __index_alphabet__(std::string machine_alphabet)
		{
			// this function fills character_ascii_indexes with numbers that represent proper sign in ascii table (usually it will be just small fragment of this table, just indexes of letters that are used by machine)
			hq::clear_int_array(Enigma::characters_ascii_indexes, 0, hq::ASCII_CHARS_AMOUNT, IRREGULAR_LETTER);

			for (int i = 0; i < machine_alphabet.size(); i++)
			{
				Enigma::alphabet[i] = machine_alphabet[i];
				Enigma::characters_ascii_indexes[(int)Enigma::alphabet[i]] = i;
			}
		}

		Disk __create_reversed_disk__(Disk starting_disk)
		{
			// function that generate reversed (index <-> values) version of specific disk (it's needed when signal is 'returning', after it reachs reflector)
			Disk reversed_disk;
			int* reversed_connections = new int[Enigma::alphabet_length];

			//std::cout << '\t';
			for (int i = 0; i < Enigma::alphabet_length; i++)
			{
				//std::cout << starting_disk.connections[i] << ' ';
				reversed_connections[starting_disk.connections[i]] = i;
				// reversed_disk.connections[starting_disk.connections[i]] = i;
			}
			
			reversed_disk.init(reversed_connections, Enigma::alphabet_length, EMPTY_NOTCH, EMPTY_NOTCH, starting_disk.rotation);
			
			return reversed_disk;
		}

		void __init_plugin_board__()
		{
			// function that prepares plug-in board without any connections between letters
			int* connections = new int[Enigma::alphabet_length];

			for (int i = 0; i < Enigma::alphabet_length; i++)
			{
				connections[i] = i;
			}
			
			Enigma::plugin_board.init(connections, Enigma::alphabet_length);
		}

		int __transcribe__(int letter, int disk_number, Disk* disks)
		{
			 // this function changes input letter according to connections in the disk
			int output = disks[disk_number].forward(letter);
			return output;
		}

	public:	// public methods
		Enigma(std::string machine_alphabet, int max_disks_amount = STANDARD_DISKS_AMOUNT)
		{
			// function that is used to prepare machine before usage

			Enigma::alphabet_length = machine_alphabet.size();
			Enigma::alphabet = new char[Enigma::alphabet_length];
			Enigma::characters_ascii_indexes = new int[hq::ASCII_CHARS_AMOUNT];

			__index_alphabet__(machine_alphabet);

			Enigma::disks_amount = 0;
			Enigma::disks = new Disk[max_disks_amount];
			Enigma::reversed_disks = new Disk[max_disks_amount];
			__init_plugin_board__();
		}

		void add_disk(int* connections, int notch, int notch_second, int rotation = 0)
		{
			// this function is used to define first / default disks

			Enigma::disks[disks_amount].init(connections, Enigma::alphabet_length, notch, notch_second, rotation);

			//disks[disks_amount].get_visual();

			Enigma::reversed_disks[Enigma::disks_amount] = __create_reversed_disk__(Enigma::disks[Enigma::disks_amount]);

			Enigma::disks_amount++;
		}

		void plug_in(char x, char y)
		{
			// this is function that allows to make a connection on plug-in board between two letters
			Enigma::plugin_board.connections[__char_to_number__(x)] = __char_to_number__(y);
			Enigma::plugin_board.connections[__char_to_number__(y)] = __char_to_number__(x);
		}

		void plug_out(char x)
		{
			// this is function that allows to disconnect two letters on plug-in board
			int y = Enigma::plugin_board.connections[__char_to_number__(x)];
			Enigma::plugin_board.connections[__char_to_number__(x)] = __char_to_number__(x);
			Enigma::plugin_board.connections[y] = y;
		}

		void change_disk(int disk_index, int* connections, int notch, int notch_second )
		{
				// this function is used to change currently used disk (from the machine) to another one
				Enigma::disks[disk_index].init(connections, Enigma::alphabet_length, notch, notch_second);
				Enigma::reversed_disks[disk_index] = __create_reversed_disk__(Enigma::disks[disk_index]);
		}
		
		void set_reflector(int* connections)
		{
			// this function is used to mount reflector into machine
			Enigma::reflector.init(connections, Enigma::alphabet_length);
		}

		void load_plugins(std::string file_name)
		{
			std::fstream input_file;
			std::string plugin;
			
			input_file.open(file_name, std::ios::in);
			
			while (input_file.eof() == false)
			{
				input_file >> plugin;
				
				if (plugin[0] != COMMENT_CHAR and plugin.size() == 2)
				{
					plug_in(plugin[0], plugin[1]);
				}
			}

			input_file.close();
		}

		hq::Pair load_connections(std::string file_name, int* connections, bool load_notches = false)
		{
			// this function is used to load array describing disk / reflector / plugin board from text file
			char letter;
		    int notch = EMPTY_NOTCH;
		    int notch_second = EMPTY_NOTCH;

			std::fstream myfile;

			myfile.open(file_name.c_str(), std::ios::in);
			for (int i = 0; i < Enigma::alphabet_length; i++)
			{
				myfile >> letter;
				connections[i] = __char_to_number__(letter);
				//std::cout << letter << ' ' << connections[i] << ' ';
			}
			
			if (load_notches == true)
			{
				myfile >> letter;
				notch = __char_to_number__(letter);

				if(!myfile.eof())
				{
					myfile >> letter;
					notch_second = __char_to_number__(letter);
				}
			}

			myfile.close();

			return hq::Pair(notch, notch_second);
			// add_disk(connections, notch , notch_second);
		}
		
		void get_visual(char input)
		{
			// char screen[alphabet_length][12 * STANDARD_DISKS_AMOUNT + 25];
			// screen[alphabet_length / 2][0] = '('; screen[alphabet_length / 2][1] = input; screen[alphabet_length / 2][2] = ')'; screen[alphabet_length / 2][3] = '='; screen[alphabet_length / 2][4] = '>';
			// for (int i)
		}

		void rotate_disk(int index, int rotation_tiks = 1)
		{
			Enigma::disks[index].rotate(rotation_tiks);
			Enigma::reversed_disks[index].rotate(rotation_tiks);
		}

		void check_rotation(int disk_index)
		{
			// this function checks if the notch is triggered and if it is , rotates the disks
			if (Enigma::disks[disk_index - 1].notch == Enigma::disks[disk_index - 1].rotation || Enigma::disks[disk_index - 1].notch_second == Enigma::disks[disk_index - 1].rotation)
			{
				// Enigma::disks[disk_index - 1].rotate(1);
				// Enigma::reversed_disks[disk_index - 1].rotate(1);
				rotate_disk(disk_index - 1);
				
				// Enigma::disks[disk_index].rotate(1);
				// Enigma::reversed_disks[disk_index].rotate(1);
				rotate_disk(disk_index);
			}
		}

		void rotation_mechanism()
		{
			if (Enigma::disks[0].notch == Enigma::disks[0].rotation || Enigma::disks[0].notch_second == Enigma::disks[0].rotation)
			{
				for(int i = 1; i < Enigma::disks_amount; i++)
				{
					check_rotation(i);
				}
			}
			else
			{
				// Enigma::disks[0].rotate(1);
				// Enigma::reversed_disks[0].rotate(1);
				rotate_disk(0);
			}
		}
		

		char encrypt_letter(char letter) // this is the encryption mechanism, it goes throught all disks(foward and back) and outputs an encrypted letter
		{
			// this function take a letter on the input, goes through every part of the machine, and returns processed, encripted version of the input
			int output = __char_to_number__(letter);

			if (output == IRREGULAR_LETTER)
			{
				return letter;
			}
			else
			{
				output = Enigma::plugin_board.forward(output);

				for (int i = 0; i < Enigma::disks_amount; i++)
				{
					//std::cout << "checkpoint " << i << '.';
					output = __transcribe__(output, i, Enigma::disks);
					//output = disks[i].forward(output);
				}

				output = Enigma::reflector.forward(output);

				for (int i = Enigma::disks_amount - 1; i >= 0; i--)
				{
					output = __transcribe__(output, i, Enigma::reversed_disks);
				}

				output = Enigma::plugin_board.forward(output);

				return __number_to_char__(output);
			}
		}

		std::string encrypt_message(std::string message)
		{
			// this function goes through every letter in message and encrypt/decrypt it using encrypt_letter function
			std::string output = "";
			
			for (int i = 0; i < message.size(); i++)
			{
				rotation_mechanism();
				//Enigma::disks[0].rotate(1);
				//Enigma::reversed_disks[0].rotate(1);
				output += encrypt_letter(hq::capital(message[i]));
			}

			return output;
		}
	};
}
