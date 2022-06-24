#include <iostream>
#include <string>
#include "libraries/enigma.h"

using namespace eng;

const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";



int main()
{
    Enigma enigma = Enigma(ALPHABET);
    
    return 0;
}