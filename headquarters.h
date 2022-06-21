// Library with some general purpose functions.
// Copyright: (!c) Public Domain | Author: <JENOT>

namespace hq
{

	// useful / "magic" numbers:
	const int ASCII_CHARS_AMOUNT = 256;


	void clear_int_array(int* array, int beginning, int end, int empty_number = 0)
	{
		for (int i = beginning; i < end; i++)
		{
			array[i] = empty_number;
		}
	}

	void clear_char_array(char* array, int beginning, int end, char empty_char = (char)0)
	{
		for (int i = beginning; i < end; i++)
		{
			array[i] = empty_char;
		}
	}

	void copy_int_array(int* sorce, int* destinaton, int lenght)
	{
		// You can also use std::copy()

		for (int i = 0; i < lenght; i++)
		{
			destinaton[i] = sorce[i];
		}
	}

}
