/*******************************************************************************
 * Program name:Final Project
 * Author:	Nicholas Weinert
 * Date:	12/02/2018
 * Description:	This is an implementation file containing the Dungeon class
 * 		The Dungeon Class inherits from the abstract Spaces class
 * 		and overrides the doAttack function
*******************************************************************************/

#include "spaces.hpp"
#include "dungeon.hpp"
#include "menu.hpp"
#include <iostream>

// The default constructor, does nothing
Dungeon::Dungeon()
{
}

// Constructor sets all of the variables to passed parameters, sets end to false
Dungeon::Dungeon(Spaces *upSpace, Spaces *downSpace, Spaces *leftSpace, Spaces *rightSpace, std::string nameRoom, std::string nameMonster)
{
        setName(nameRoom);
        setMonster(nameMonster);
        up = upSpace;
        down = downSpace;
        left = leftSpace;
        right = rightSpace;
	setEnd(false);
}

/********************************************************************************
 * doAttack simulates attacking a monster for each room inside of the dungeon.
 * It "creates" a monster by implementing a health for value to attack. The
 * function also creates a menu to choose a weapon and simulates attacks
 * by the monster onto the character
********************************************************************************/
int Dungeon::doAttack(int playerHealth)
{
        int effective, i = 0;
	int weapon = -1;
	int change = -1;
	int monsterHealth = rand() % 200 + 1;
	int damage = 0;
	int damageTaken = 0;
        std::string input = "";
        Menu menu1(4);
        menu1.fillMenu(1,"Playing Cards");
        menu1.fillMenu(2,"Frying Pan");
        menu1.fillMenu(3,"Sandal");
        menu1.fillMenu(4,"Sawed-Off Shotgun");
	Menu menu2(2);
	menu2.fillMenu(1,"Yes");
	menu2.fillMenu(2,"No");

	// Tell the user what room they are in and who they are fighting
        std::cout << "\nOh no! You entered the " << getName() << " and " << 
		getMonster() << " was waiting for you." << std::endl;
        std::cout << "What weapon would you like to attack with?" << std::endl;
        // Simulate the attack
	do
	{	// Give each weapon a random effectiveness
		effective = rand() % 4 + 1;
		change = -1;
	        do
		{
	                std::cout << "Please select a weapon (1-4)" << std::endl;
	        	menu1.printMenu();
	        	std::cin.putback(' ');
	        	getline(std::cin,input);
	        	weapon = menu1.returnInt(input,1,4);
        	}while(weapon == -1);

		do
		{	// have the monster attack the character first
			damageTaken = damageTaken + (rand() % 5 + 1);
			// if the damage taken would kill the character, return the players health
			// to set the character health to 0
			if(damageTaken >= playerHealth)
			{
				return playerHealth;
			}
			change = -1;

			// Do the attack and tell the user about it. 4 is most effective, 1 is least
			switch(effective)
			{
				case 4:
				{
					damage = rand() % 25 + 1 + 75;
					std::cout << "Great attack! Damage dealt"
						<< " to " << getMonster() << " is: " <<
						damage << ". \n" << getMonster() << 
						" health is now: " << monsterHealth - damage
						<< std::endl;
					monsterHealth -= damage;
					break;
				}
				case 3:
				{
					damage = rand() % 25 + 1 + 25;
					std::cout << "Decent strike! Damage dealt"
						<< " to " << getMonster() << " is: " <<
						damage << ". \n" << getMonster() << 
						" health is now: " << monsterHealth - damage
						<< std::endl;
					monsterHealth -= damage;
					break;
				}
				case 2:
				{
					damage = rand() % 25 + 1;
					std::cout << "You call that an attack?! Damage dealt"
						<< " to " << getMonster() << " is: " <<
						damage << ". \n" << getMonster() << 
						" health is now: " << monsterHealth - damage
						<< std::endl;
					monsterHealth -= damage;
					break;
				}
				case 1:
				{
					damage = 0;
					std::cout << "You missed completely! No damage dealt"
						<< " to " << getMonster() << "." << std::endl;
					break;
				}
				default:
					break;
	
			}

			// Ask the user if they want to change weapons. This will re-do the random
			// effectiveness
			while(change == -1 && monsterHealth > 0)
			{
				std::cout << "Would you like to change weapons?" << std::endl;
				menu2.printMenu();
		        	std::cin.putback(' ');
		        	getline(std::cin,input);
			        change = menu2.returnInt(input,0,2);
			}
	
			if(change == 1)
			{
				weapon = -1;
			}
		}while(monsterHealth > 0 && change != 1);
	}while(weapon == -1 && monsterHealth > 0);

	return damageTaken;
}
