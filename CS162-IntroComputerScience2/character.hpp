/*******************************************************************************
 * Program name:Final Project
 * Author:	Nicholas Weinert
 * Date:	12/02/2018
 * Description:	This is a header file containing the Character class
 * 		The character class defines a character that must escape a 
 * 		Haunted House for the final project. The Character tracks where
 * 		in the house it is and has functions to attack monsters
 * 		and keep track of health and hold things in a satchel. 
 * 		There is also a function to takea actions after defeating a 
 * 		monster.
*******************************************************************************/



#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <string>
#include <vector>
#include "spaces.hpp"

class Character
{
	protected:
		std::vector<int> satchel;
		int health, weapon, spacesSearched;
		std::string name;
		Spaces *currentSpace;

	public:
		Character();
		void optionsMenu(Spaces *);
		void attack();
		void searchSpace();

		std::string getName();
		int getWeapon();
		void setWeapon(int);
		void setSpace(Spaces *);
		int getSatchel();
		void printSatchel();
		void setSpacesSearched(int);
		int getSpacesSearched();
		bool getDead();
		void setHealth(int);
		int getHealth();
};
#endif
