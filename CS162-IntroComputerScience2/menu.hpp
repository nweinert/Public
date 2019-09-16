/********************************************************************************************
 * Program name:Project 1 - Langton's Ant
 * Author:	Nicholas Weinert
 * Date:	10/07/2018
 * Description:	This is a header file containing for the Menu class
 * 		The Menu class defines some simple reusable functions for 
 * 		creating and filling a Menu as well as validating integer
 * 		input. This class will expand throughout the term as more
 * 		validation functions are needed.
********************************************************************************************/



#ifndef MENU_HPP
#define MENU_HPP
#include <string>


class Menu
{
	private:
		std::string *optionText;
		int numMenuOptions;
	
	
	public:
		Menu();
		Menu(int numMenuOptions);
		void printMenu();
		void fillMenu(int,std::string);
		void setInputValidationTrue();
		void fillMenu();
		int returnInt(std::string);
		int returnInt(std::string, int min, int max);
		char returnChar(std::string);
		~Menu();

	
};
#endif

