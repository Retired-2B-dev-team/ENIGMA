// Library with some useful (I hope) stuff for implementing ENIGMA machine simulations
// 1/14/2022	<Antoni Świtaj>

#include <fstream>
#include <string>

#include "headquarters.h" // namespace: "hq"



namespace egma
{

	const int STANDARD_ALPHABET_LENGHT = 26; // lenght of the alphabet used by the machine
	const int STANDARD_DISKS_AMOUNT = 3;	 // amount of disks with letters, used in the machine


	class Disk
	{

	private: // private attributes
		int* connections; // an array describing the disk construction
		int rotation;
		int alphabet_lenght;

	private: // private methods
		void __correct_rotation__()
		{
			if (rotation >= alphabet_lenght)
			{
				rotation -= alphabet_lenght;
			}
			else if (rotation < 0)
			{
				rotation += (alphabet_lenght - 1);
			}
		}

	public: // public methods
		void load(std::string file_name)
		{
		}

		void init(int alphabet_size)
		{
			alphabet_lenght = alphabet_size;
			connections = new int[alphabet_lenght];
			rotation = 0;
		}

		void rotate(bool vector)
		{

			if (vector == true)
			{
				rotation += 1;
			}
			else
			{
				rotation -= 1;
			}
			__correct_rotation__();
		}
	};

	class Enigma
	{

	private: // private attributes
		char* alphabet; // ENIGMA machine's alphabet array
		int* characters_ascii_indexes;
		Disk* disks;

		int alphabet_lenght;

	private: // private methods
		void __index_alphabet__(std::string machine_alphabet)
		{
			for (int i = 0; i < machine_alphabet.size(); i++)
			{
				alphabet[i] = machine_alphabet[i];
				characters_ascii_indexes[(int)alphabet[i]] = i;
			}
		}

	public:	// public methods
		void init(std::string machine_alphabet)
		{
			alphabet_lenght = machine_alphabet.size();
			alphabet = new char[alphabet_lenght];
			characters_ascii_indexes = new int[hq::ASCII_CHARS_AMOUNT];

			__index_alphabet__(machine_alphabet);
		}

		void add_disk()
		{
		}
	};

}
