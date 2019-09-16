/*******************************************************************************
 * Program name:Final Project
 * Author:	Nicholas Weinert
 * Date:	12/02/2018
 * Description:	This is an implementation file containing the House class
 * 		The House class inherits from the abstract Spaces class
 * 		and overrides the doAttack function
*******************************************************************************/

#include "spaces.hpp"
#include "house.hpp"
#include "menu.hpp"

#include <iostream>

// base constructor, does nothing
House::House()
{
}

// Constructor sets all of the variables to passed parameters, sets end to false
House::House(Spaces *upSpace, Spaces *downSpace, Spaces *leftSpace, Spaces *rightSpace, std::string nameRoom, std::string nameMonster)
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
 * doAttack simulates attacking a monster for each room inside of the house.
 * It "creates" a monster by implementing a health for value to attack. The
 * function also creates a menu to choose a weapon and simulates attacks
 * by the monster onto the character. This is extremely similar to the dungeon
 * doAttack, but adds an option to try to hide from the monster
********************************************************************************/
int House::doAttack(int playerHealth)
{
        int effective, i = 0;
	int weapon = -1;
	int change = -1;
	int monsterHealth = rand() % 200 + 100;
	int damage = 0;
	int damageTaken = 0;
        std::string input = "";
        Menu menu1(5);
        menu1.fillMenu(1,"Kitchen Knife");
        menu1.fillMenu(2,"Fire Poker");
        menu1.fillMenu(3,"Door Knob");
        menu1.fillMenu(4,"Bleach Spray");
        menu1.fillMenu(5,"Hide instead of attacking");
	Menu menu2(2);
	menu2.fillMenu(1,"Yes");
	menu2.fillMenu(2,"No");

	// tell the user the room and monster name
        std::cout << "\nOh no! You entered the " << getName() << " and " << 
		getMonster() << " was waiting for you." << std::endl;
        std::cout << "What weapon would you like to attack with?" << std::endl;
        // do attack
	do
	{	// random weapon effectiveness
		effective = rand() % 4 + 1;
		change = -1;
		//select weapon
	        do
		{
	                std::cout << "Please select a weapon (1-5)" << std::endl;
	        	menu1.printMenu();
	        	std::cin.putback(' ');
	        	getline(std::cin,input);
	        	weapon = menu1.returnInt(input,1,5);
        	}while(weapon == -1);
		// if the user chooses to hide, 25% chance that it will work
		if(weapon == 5)
		{	
			int leave = rand() % 4;
			// 1 in 4 times, kill the monster and return no damage to character
			// health
			if(leave == 0)
			{
				std::cout << "You hid and " << getMonster() << 
					" left the room! You escaped!" << std::endl;
				monsterHealth = -1;
				return 0;
			}
			else
			{
				std::cout << "You hid, but " << getMonster() << 
					" found you. It's a fist fight!" << std::endl;
			}
		}
		// do the attack the same as dungeon class if the user selects a weapon
		// OR if the hiding did not work
		do
		{	// monster attacks first
			damageTaken = damageTaken + (rand() % 5 + 1);
			if(damageTaken >= playerHealth)
			{
				return playerHealth;
			}
			change = -1;
			// Switch based on the random effectiveness, the same as dungeon class
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
