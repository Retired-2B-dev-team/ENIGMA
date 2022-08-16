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

	const int STANDARD_ALPHABET_LENGHT = 26; // lenght of the alphabet used by the machine
	const int STANDARD_DISKS_AMOUNT = 3;	 // amount of disks with letters, used in the machine


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
			int output = rotation + __index;

			if (output >= size)
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
			rotation = 0;

			size = __disk_size;
			connections = new int[size];

			std::copy(__connections, __connections + size, connections);
		}

		void rotate(int __rotation_tiks)
		{
			rotation += __rotation_tiks;
			__correct_rotation__();
		}

		int forward(int index)
		{
			return connections[__normalize__(index)];
		}
	};

	class Enigma
	{

	private: // private attributes
		char* alphabet; // ENIGMA machine's alphabet array
		int* characters_ascii_indexes;

	public:
		Disk plugin_board;
		Disk* disks;
		Disk reflector; // reversing roller
		Disk* reversed_disks;
		int disks_amount;

		int alphabet_lenght;

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
			for (int i = 0; i < __machine_alphabet.size(); i++)
			{
				alphabet[i] = __machine_alphabet[i];
				characters_ascii_indexes[(int)alphabet[i]] = i;
			}
		}

		Disk __create_reversed_disk__(Disk __starting_disk)
		{
			Disk reversed_disk{};
			int* reversed_connections = new int[__starting_disk.size];
			
			for (int i = 0; i < __starting_disk.size; i++)
			{
				reversed_connections[__starting_disk.connections[i]] = i;
				// reversed_disk.connections[__starting_disk.connections[i]] = i;
			}
			
			reversed_disk.init(reversed_connections, __starting_disk.size);
			
			return reversed_disk;
		}

		void __init_plugin_board__()
		{
			int* __connections = new int[alphabet_lenght];

			for (int i = 0; i < alphabet_lenght; i++)
			{
				__connections[i] = i;
			}
			
			plugin_board.init(__connections, alphabet_lenght);
		}

	public:	// public methods
		Enigma(std::string __machine_alphabet, int __max_disks_amount = STANDARD_DISKS_AMOUNT)
		{
			alphabet = new char[alphabet_lenght];
			characters_ascii_indexes = new int[hq::ASCII_CHARS_AMOUNT];
			alphabet_lenght = __machine_alphabet.size();

			__index_alphabet__(__machine_alphabet);

			disks_amount = 0;
			disks = new Disk[__max_disks_amount];
			reversed_disks = new Disk[__max_disks_amount];
			__init_plugin_board__();
		}

		void add_disk(int* __connections)
		{
			disks[disks_amount].init(__connections, alphabet_lenght);

			reversed_disks[disks_amount] = __create_reversed_disk__(disks[disks_amount]);

			disks_amount++;
		}

		void plug_in(char x, char y)
		{
			plugin_board.connections[__char_to_number__(x)] = __char_to_number__(y);
			plugin_board.connections[__char_to_number__(y)] = __char_to_number__(x);
		}

		void change_disk(int disk_index, int* __connections)
		{
			disks[disk_index].init(__connections, alphabet_lenght);
			reversed_disks[disk_index] = __create_reversed_disk__(disks[disk_index]);
		}

		void set_reflector(int* __connections)
		{
			reflector.init(__connections, alphabet_lenght);
		}

		void load_connections(std::string __file_name, int* __connections)
		{
			char letter;
			__connections = new int[alphabet_lenght];
			std::fstream myfile;

			myfile.open(__file_name.c_str(), std::ios::in);
			for (int i = 0; i < alphabet_lenght; i++)
			{
				myfile >> letter;
				__connections[i] = __char_to_number__(letter);
			}
			myfile.close();
			// add_disk(__connections);
		}
		
		std::string get_visual()
		{
			std::string output = "";
			
			for (int i = 0; i < disks_amount; i++)
			{
				for (int j = 0; j < alphabet_lenght; j++)
				{
					output += __number_to_char__(j);
					output += ": ";
					output += __number_to_char__(disks[i].forward(j));
					output += ", ";
				}
				output += "\n\n";
			}
			
			return output;
		}
		
		int transcribe(int __letter, int __disk_number, Disk* __disks) // this function changes input letter according to connections in the disk
		{
			int output = __disks[__disk_number].forward(__char_to_number__(__letter));
			return output;
		}


		char encrypt(char __letter) // this is the encryption mechanism , it goes throught all disks(foward and back) and outputs an encrypted letter
		{
			int output = __char_to_number__(__letter);

			for (int i = 0; i < disks_amount; i++)
			{
				output = transcribe(output, i, disks);
			}

			output = reflector.forward(output);
			
			for (int i = disks_amount - 1; i >= 0; i--)
			{
				output = transcribe(output, i, reversed_disks);
			}

			return __number_to_char__(output); 
		}
	};
}
