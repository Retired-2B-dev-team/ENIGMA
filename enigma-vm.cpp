#include <iostream>
#include <string>
#include "libraries/enigma.h"


using namespace eng;

const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int main()
{
    int connections1[STANDARD_ALPHABET_LENGHT] = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
            10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
            20, 21, 22, 23, 24, 25
    };
    int connections2[STANDARD_ALPHABET_LENGHT] = {
            25, 24, 23, 22, 21, 20,
            19, 18, 17, 16, 15, 14, 13, 12, 11, 10,
            9, 8, 7, 6, 5, 4, 3, 2, 1, 0
    };

    Enigma enigma = Enigma(ALPHABET);

    enigma.add_disk(connections1);
    enigma.add_disk(connections2);
    enigma.disks[0].rotate(2);

    std::cout << enigma.get_visual();
    return 0;
}