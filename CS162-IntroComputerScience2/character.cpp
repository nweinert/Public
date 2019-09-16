/*******************************************************************************
 * Program name:Final Project
 * Author:	Nicholas Weinert
 * Date:	12/02/2018
 * Description:	This is an implementation file containing the Character class
 * 		The character class defines a character that must escape a 
 * 		Haunted House for the final project. The Character tracks where
 * 		in the house it is and has functions to attack monsters
 * 		and keep track of health and hold things in a satchel. 
 * 		There is also a function to takea actions after defeating a 
 * 		monster.
*******************************************************************************/

#include "character.hpp"
#include "spaces.hpp"
#include "menu.hpp"
#include <iostream>

// Base constructor for the character class. Sets everything equal to 0
Character::Character()
{
	setHealth(100);
	setWeapon(-1);
	std::cout << "\nPlease enter the name for your character." << std::endl;
	getline(std::cin,name);
	setSpacesSearched(0);
}

/******************************************************************************
 * the attack() function checks to see if that space has been cleared already,
 * and if it has it tells the user that it's been cleared. If not, it calls 
 * the spaces do attack to fight the monster
******************************************************************************/
void Character::attack()
{
	if(currentSpace->getCleared())
	{
		std::cout << "You entered " << currentSpace->getName()
			<< " but you already beat the monster."
			<< std::endl;
	}
	else
	{
		// space->doAttack returns the damage taken by the character
		// This line subtracts that value when calling doAttack
		setHealth(getHealth() - currentSpace->doAttack(getHealth()));
		currentSpace->setCleared(true);
	}
}

/******************************************************************************
 * searchSpace randomly lets the user find either strange metal (for keys, 
 * needed to win the game) or health. It repeats until the user takes something
 * and sets the spaceSearched value to true, which prevents the space from
 * being searched again. 
******************************************************************************/
void Character::searchSpace()
{
	std::string input = "";
	int intInput = -1;

	Menu searchMenu(3);
	searchMenu.fillMenu(1,"Take item.");
	searchMenu.fillMenu(2,"Keep searching.");
	searchMenu.fillMenu(3,"Leave Room.");

	// While the user selects something invalid or to keep searching, 
	// do the search
	while(intInput == -1 || intInput == 2)
	{
		int random = rand() % 3 + 1;
		switch(random)
		{
			case 1:
			{	// Take input for whether to take some health
				int healthBoost = rand() % 15 + 5;
				std::cout << "You found some health potions!" << std::endl;
				while(intInput == -1)
				{
					std::cout << "What would you like to do?" << std::endl;
					searchMenu.printMenu();
					std::cin.putback(' ');
					getline(std::cin, input);
					intInput = searchMenu.returnInt(input,1,3);
					if(intInput == 1)
					{
						std::cout << healthBoost << " has been added "
							<< "to your health." << std::endl;
						setHealth(getHealth() + healthBoost);
					}
				}
				break;
			}
			case 2:
			{	// Take input for stange metal
				std::cout << "You found some strange metal." << std::endl;
				while(intInput == -1)
				{
					std::cout << "What would you like to do?" << std::endl;
					searchMenu.printMenu();
					std::cin.putback(' ');
					getline(std::cin, input);
					intInput = searchMenu.returnInt(input,1,3);
					if(intInput == 1)
					{
						std::cout << "You put it in your satchel." << std::endl;
						satchel.push_back(1);
					}
				}
				break;
			}
			default:
				break;
		}
		if(intInput == 2)
		{
			intInput = -1;
		}

	}

	// set current space to searched and count the space as searched
	if(intInput != 3)
	{
		currentSpace->setSearched(true);
		setSpacesSearched(getSpacesSearched() + 1);
	}
}

/******************************************************************************
 * optionsMenu allows the user to take some actions after beating the monster 
 * in the current space. It takes a pointer to the final space in the game 
 * so that it can stop the user from going outside unless they have first
 * cleared the entire house
******************************************************************************/
void Character::optionsMenu(Spaces* outside1)
{
	// Define the menu and variables
        int intInput = -1;
	std::string input = "";
        Menu menu1(8);
        menu1.fillMenu(1,"See remaining health");
        menu1.fillMenu(2,"View items in bag");
        menu1.fillMenu(3,"View map");
        menu1.fillMenu(4,"Search room");
        menu1.fillMenu(5,"Move up");
        menu1.fillMenu(6,"Move down");
        menu1.fillMenu(7,"Move left");
        menu1.fillMenu(8,"Move right");

        std::cout << "What action would you like to take next?" << std::endl;

	// While the user prints the map, satchel, health or searches the room 
	while(intInput == 1 || intInput == 2 || intInput == 3 || intInput == 4 || intInput == -1)
	{
		// print the menu and take input
	        do
	        {
	                std::cout << "Please select a valid option (1-8)" << std::endl;
	                menu1.printMenu();
	                std::cin.putback(' ');
	                getline(std::cin,input);
	                intInput = menu1.returnInt(input,1,8);
       		}while(intInput == -1);
	
		// switch based on the menu values
	        switch(intInput)
	        {
                	case 1:
                	{
                	        std::cout << "Your players health is: " << getHealth() << std::endl;
                	        break;
                	}
                	case 2:
                	{
                	        printSatchel();
                	        break;
                	}
                 	case 3:
                	{
                	        currentSpace->printMap();
				std::cout << "You are currently in " << currentSpace->getName() << std::endl;
                	        break;
                	}
                	case 4:
                	{
				if(currentSpace->getSearched())
				{
					std::cout << "You already searched this space!" << std::endl;
				}
				else
				{
                	        	searchSpace();
				}
                	        break;
                	}      
                	case 5:
                	{
				// If UP is outside and you haven't searched the
				// whole house yet, don't let them leave
				if(currentSpace->getUp() == outside1 && getSpacesSearched() != 8)
				{
					std::cout << "You can't leave the house until you have searched "
						<< "all the rooms." << std::endl;
					optionsMenu(outside1);
				}// If up is actually something, go up
				else if(currentSpace->getUp() != nullptr)
				{
                	        	setSpace(currentSpace->getUp());
                	        }
				else
				{
					std::cout << "That is just a wall! Try another direction." << std::endl;
					optionsMenu(outside1);
				}
				break;
                	}
                	case 6:
                	{	// if down is something, go down
 				if(currentSpace->getDown() != nullptr)
				{
                	       		setSpace(currentSpace->getDown());
                	        }
				else
				{
					std::cout << "That is just a wall! Try another direction." << std::endl;
					optionsMenu(outside1);
				}
                	       break;
                	}
                	case 7:
                	{
 				if(currentSpace->getLeft() != nullptr)
				{
                		       setSpace(currentSpace->getLeft());
                	        }
				else
				{
					std::cout << "That is just a wall! Try another direction." << std::endl;
					optionsMenu(outside1);
				}
                	       break;
                	}
                	case 8:
                	{
				if(currentSpace->getRight() != nullptr)
				{
        		               setSpace(currentSpace->getRight());
                	        }
				else
				{
					std::cout << "That is just a wall! Try another direction." << std::endl;
					optionsMenu(outside1);
				}
                	       break;
                	}
                	default:
                	        break;
        	}
	}
}

/******************************************************************************
 * The following are simply getters, setters or print functions
******************************************************************************/
void Character::setWeapon(int newWeapon)
{
        weapon = newWeapon;
}

int Character::getWeapon()
{
        return weapon;
}

bool Character::getDead()
{
	if(getHealth() > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Character::printSatchel()
{
	std::cout << "You have " << satchel.size() << " pieces of strange metal "
		<< "in your satchel." << std::endl;
}

void Character::setHealth(int newHealth)
{
	health = newHealth;
}

int Character::getHealth()
{
	return health;
}

std::string Character::getName()
{
        return name;
}

void Character::setSpace(Spaces *newSpace)
{
	currentSpace = newSpace;
}

int Character::getSatchel()
{
	return satchel.size();
}

void Character::setSpacesSearched(int newSpaces)
{
	spacesSearched = newSpaces;
}

int Character::getSpacesSearched()
{
	return spacesSearched;
}
