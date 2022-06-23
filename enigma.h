// Library with some useful (I hope) stuff for implementing ENIGMA machine simulations
// 1/14/2022	<Antoni Świtaj>

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
						  by 1D vectors
*/

#include <fstream>
#include <string>
#include <algorithm>

#include "headquarters.h" // namespace: "hq"



namespace eng
{

	const int STANDARD_ALPHABET_LENGHT = 26; // lenght of the alphabet used by the machine
	const int STANDARD_DISKS_AMOUNT = 3;	 // amount of disks with letters, used in the machine


	class Disk
	{
		
	private: // private attributes
		int* connections; // an array describing the disk construction
		int rotation;
		int disk_size; // amount of letters on the single disk

	private: // private methods
		void __correct_rotation__()
		{
			while (rotation >= disk_size)
			{
				rotation -= disk_size;
			}
			while (rotation < 0)
			{
				rotation += (disk_size - 1);
			}
		}

	public: // public methods
		void load(std::string file_name)
		{
			// this function should load the disk's letter connections from file and initialize disk
		}

		void init(int* __connections, int __disk_size)
		{
			rotation = 0;
			
			disk_size = __disk_size;
			connections = new int[disk_size];

			std::copy(__connections, __connections + disk_size, connections);
		}

		void rotate(int __rotation_tiks)
		{
			rotation += __rotation_tiks;
			__correct_rotation__();
		}
	};

	class Enigma
	{

	private: // private attributes
		char* alphabet; // ENIGMA machine's alphabet array
		int* characters_ascii_indexes;

		Disk* disks;
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

	public:	// public methods
		Enigma(std::string __machine_alphabet, int __max_disks_amount = STANDARD_DISKS_AMOUNT)
		{
			alphabet_lenght = __machine_alphabet.size();
			alphabet = new char[alphabet_lenght];
			characters_ascii_indexes = new int[hq::ASCII_CHARS_AMOUNT];

			__index_alphabet__(__machine_alphabet);

			disks_amount = 0;
			disks = new Disk[__max_disks_amount];
			reversed_disks = new Disk[__max_disks_amount];
		}

		void add_disk(int* __connections)
		{
			disks[disks_amount].init(__connections, alphabet_lenght);

			disks_amount++;
		}
	};

}
