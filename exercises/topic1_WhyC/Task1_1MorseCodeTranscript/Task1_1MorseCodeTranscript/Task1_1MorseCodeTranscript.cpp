// Task1_1MorseCodeTranscript.cpp : 
//
// Reads input in Morse and translates it to english
//
// According to https://en.wikipedia.org/wiki/Morse_code:
//The duration of a dash is three times the duration of a dot.Each dot or dash is followed by a short silence, 
//equal to the dot duration.The letters of a word are separated by a space equal to three dots(one dash), 
//and the words are separated by a space equal to seven dots.
//
// Therefore, the required input format will use ., - and _ as delimiter
// TODO: Make it work with whitespace symbols as well
//
// Example:
//
// .---_..-_--_.--._______.-_.-._---_..-_-._-..___.-
//
// would translate to and output:
//
// "Jump around-a"
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctype.h>

char* EnglishToMorse(std::string latinText) {
	char latinCharacters[36] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9' };
	std::string morseCodeCharacters[36] = {
		".-",
		"-...",
		"-.-.",
		"-..",
		".",
		"..-.",
		"--.",
		"....",
		"..",
		".---",
		"-.-",
		".-..",
		"--",
		"-.",
		"---",
		".--.",
		"--.-",
		".-.",
		"...",
		"-",
		"..-",
		"...-",
		".--",
		"-..-",
		"-.--",
		"--..",
		"-----",
		".----",
		"..---",
		"...--",
		"....-",
		".....",
		"-....",
		"--...",
		"---..",
		"----."
	};
	std::string output;
	std::string wsBetweenLetters = "_";
	std::string wsBetweenDots = "__"; //2 characters +1 wsBetweenLetters = 3 characters
	std::string wsBetweenWords = "______"; //6 characters +1 coming from wsBetweenLetters = 7 characters

	int i = 0;
	char currentLetter;
	int j;
	while (i != '\0')
	{
		currentLetter = latinText[i];
		//TODO: use switch statement instead and define a locale
		//std::locale latin("en-US");

		if (isalpha(currentLetter) || isdigit(currentLetter)) {
			for (int j = 0; j < 36; j++)
			{
				if (latinCharacters[j] == toupper(currentLetter)) {
					output += morseCodeCharacters[j];
				}
			}
			output += wsBetweenLetters;
		} else if (isspace(currentLetter)) {
			output += wsBetweenWords;
		}

		//Don't forget the dash!

		//We ignore all other characters for now
		i++;
	}

	char *translation = new char[output.length() + 1];
	strcpy_s(translation, output.length() + 1, output.c_str());

	return translation;
}

int main(int argc, char **argv)
{
	std::cout<<EnglishToMorse("Holla");
	system("pause");
	return 0;
};