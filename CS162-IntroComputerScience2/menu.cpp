/*******************************************************************************
 * Program name:Project 1 - Langton's Ant
 * Author:	Nicholas Weinert
 * Date:	10/07/2018
 * Description:	This is an implementation file containing for the Menu class
 * 		The Menu class defines some simple reusable functions for 
 * 		creating and filling a Menu as well as validating integer
 * 		input. This class will expand throughout the term as more
 * 		validation functions are needed.
*******************************************************************************/

#include "menu.hpp"
#include <iostream>

/***************************************************************************
 * The following are constructors for the Menu class. A default that sets the
 * number of options to 0 and one that takes the number of options as a 
 * parameter and creates an array. The default is not used much.
***************************************************************************/
Menu::Menu()
{
	numMenuOptions = 0;
}


Menu::Menu(int options)
{
	numMenuOptions = options;
	optionText = new std::string[numMenuOptions];
}


/**************************************************************************
 * The printMenu function simply prints the menu to the screen
**************************************************************************/

void Menu::printMenu()
{
	for(int i = 0; i < numMenuOptions; i++)
		std::cout << i+1 << ".\t" << optionText[i] << std::endl;
}

/*************************************************************************
 * This fillMenu function allows for a user to fill a menu with different
 * options while the program is running. It is not used in Project 1 but 
 * may have uses later.
************************************************************************/

void Menu::fillMenu()
{
	for(int i = 0; i < numMenuOptions; i++)
	{
		std::cout << "Enter text for option " << i << "." <<std::endl;
		getline(std::cin,optionText[i]);
	}

}

/**************************************************************************
 * The fillMenu function fills the menu array with text specified by the 
 * writer of the implementation file
*************************************************************************/

void Menu::fillMenu(int number, std::string input)
{
	optionText[(number-1)] = input;
}


/***************************************************************************
 * The returnInt function allows the verification that an in was entered
 * within a certain range of integers. If what was entered was not an integer
 * or was out of range the function will return -1
***************************************************************************/

int Menu::returnInt(std::string newInput)
{
	int integerInput = 0;
	bool inputValidation = true;
	std::string input = "";

	if(newInput.length() > 1)
		input = newInput.erase(0,1);
	else
		input = newInput;

// checking for any characters
		for(int i = 0; i < input.length();i++)
			if(!isdigit(input[i]) && input[0] != '-')
				inputValidation = false;
// once we show that there are no characters, set it into an integer.
		if(inputValidation == true)
			integerInput = std::stoi(input);

	return integerInput;
}

int Menu::returnInt(std::string newInput,int min,int max)
{
	int integerInput = 0;
	bool inputValidation = true;
	std::string input = "";

	if(newInput.length() > 1)
		input = newInput.erase(0,1);
	else
		input = newInput;

// checking for any characters
		for(int i = 0; i < input.length();i++)
			if(!isdigit(input[i]) && input[0] != '-')
				inputValidation = false;
// once we show that there are no characters, set it into an integer.
		if(inputValidation == true)
		{
			integerInput = std::stoi(input);
			if(integerInput < min || integerInput > max)
				inputValidation = false;
		}
	if (inputValidation == false)
		return -1;
	else
		return integerInput;
}
/* This can and will be expanded on in the future
char returnChar(std::string input)
{

}
*/

Menu::~Menu()
{
	delete [] optionText;
}
