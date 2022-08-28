// Library with some general purpose functions.
// Copyright: (!c) Public Domain | Author: <JENOT>
#include <fstream>
#include <string>
#include <vector>

namespace hq
{

	// useful / "magic" numbers:
	const int ASCII_CHARS_AMOUNT = 256;

	struct Pair
	{
	public:
		int x;
		int y;
		
		Pair (int x, int y)
		{
			Pair::x = x;
			Pair::y = y;
		}
	};

	int normalize(int value, int max)
	{
		return value % max;
	}
	
	bool is_lower(char letter)
	{
		if ((int)letter >= 97 && (int)letter <= 122)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	char capital(char letter)
	{
		if (is_lower(letter) == true)
		{
			return (char)(letter - 32);
		}
		else
		{
			return letter;
		}
	}

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

	namespace cmd
	{
		const char SEPARATOR = '-';
		
		std::vector<std::string> separate_args(int argc, char** argv)
		{
			std::string argument;
			std::vector<std::string> output;
			std::string word;
			
			for (int i = 1; i < argc; i++) // for each argument
			{
				argument = std::string(argv[i]);

				
				if (argument[0] == SEPARATOR && argument.size() > 1) // if it's an argument
				{

					if (argument[1] == SEPARATOR && argument.size() > 2) // --full_name
					{
						word = "";
						
						for (int j = 2; j < argument.size(); j++)
						{
							word += argument[j];
						}

						output.push_back(std::string("--") + word);
					}
					else // -abc
					{
						for (int j = 1; j < argument.size(); j++)
						{
							word = "-";
							word += argument[j];
							output.push_back(word);
						}
					}
				}
				else // if it's input
				{
					output.push_back(argument);
				}
			}

			return output;
		}
		// class Arg
		// {
		// public:
		// 	bool read_next;
		// 	char alias;
		// 	std::string full_name;

		// 	void init (char __alias, std::string __full_name, bool __read_next)
		// 	{
		// 		alias = __alias;
		// 		full_name = __full_name;
		// 		read_next = __read_next;
		// 	}
		// };

		// class CMD_handler
		// {
		// 	int args_amount;
		// 	int max_args_amount;
		// 	Arg* args;

		// 	CMD_handler(int __max_args_amount)
		// 	{
		// 		max_args_amount = __max_args_amount;
		// 		args = new Arg[max_args_amount];
		// 	}

		// 	void add_arg(char __alias, std::string __full_name, bool __read_next)
		// 	{
		// 		args[args_amount].init(__alias, __full_name, __read_next);
		// 	}
		// };
	}
}
