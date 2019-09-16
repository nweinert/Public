/*******************************************************************************
 * Program name:Final Project
 * Author:	Nicholas Weinert
 * Date:	12/02/2018
 * Description:	This is an implementation file containing the Outside class
 * 		The Outside class inherits from the abstract Spaces class
 * 		and overrides the doAttack function
*******************************************************************************/

#include "spaces.hpp"
#include "outside.hpp"
#include "menu.hpp"

#include <iostream>

// Base constructor doesn't do anything
Outside::Outside()
{
}

// Constructor sets all of the variables to passed parameters, sets end to false
Outside::Outside(Spaces *upSpace, Spaces *downSpace, Spaces *leftSpace, Spaces *rightSpace, std::string nameRoom, std::string nameMonster)
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
 * doAttack simulates attacking a fire-breathing dragon outside.
 * It "creates" a monster by implementing a health for value to attack. The
 * function also creates a menu to choose a weapon and simulates attacks
 * by the monster onto the character. This is extremely similar to the dungeon
 * doAttack, but adds an option to try to hide from the monster
********************************************************************************/
int Outside::doAttack(int playerHealth)
{
        int effective, i = 0;
	int weapon = -1;
	int change = -1;
	// Dragon has a lot of health
	int monsterHealth = 750;
	int damage = 0;
	int damageTaken = 0;
        std::string input = "";
        Menu menu1(4);
        menu1.fillMenu(1,"Punch");
        menu1.fillMenu(2,"Kick");
        menu1.fillMenu(3,"Poke its eye");
        menu1.fillMenu(4,"Drown it");
	Menu menu2(2);
	menu2.fillMenu(1,"Yes");
	menu2.fillMenu(2,"No");


        std::cout << "\nFinally!! You made it outside and escaped the house!"
		<< std::endl;
	// This loop just prints a period on a line every 2 seconds. You know,
	// for dramatic effect
	for(int i = 0; i < 3; i++)
	{
		int temp = time(NULL) + 2;
		while(temp > time(NULL));
		std::cout << "." << std::endl;
	}
	std::cout << "What is that?" << std::endl;
	// Same super dramatic loop as above
	for(int i = 0; i < 3; i++)
	{
		int temp = time(NULL) + 2;
		while(temp > time(NULL));
		std::cout << "." << std::endl;
	}
	std::cout << "A FIRE-BREATHING DRAGON!!\nYou have to fight it, but you have no weapons!"
		 << std::endl;
        // Very similar attack do-while + switch combo as in dungeon and house
	do
	{
		effective = rand() % 4 + 1;
		change = -1;
	        do
		{
	                std::cout << "Please select an attack (1-4)" << std::endl;
	        	menu1.printMenu();
	        	std::cin.putback(' ');
	        	getline(std::cin,input);
	        	weapon = menu1.returnInt(input,1,4);
        	}while(weapon == -1);

		do
		{	// Die if damage taken is greater than health
			damageTaken = damageTaken + (rand() % 5 + 1);
			if(damageTaken >= playerHealth)
			{
				return playerHealth;
			}
			change = -1;
			// switch based on random effectiveness
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

	std::cout << "You killed the dragon! As it dies it lets out his last breath." 
		<< "\nThe fire is intense!" << std::endl;

	setEnd(true);


	return damageTaken;
}
