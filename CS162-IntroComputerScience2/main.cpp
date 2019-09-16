/*******************************************************************************
 * Program name:Final Project
 * Author:	Nicholas Weinert
 * Date:	12/02/2018
 * Description:	This is the main function for the haunted house game. It creates
 * 		and links the different spaces and the character. It also then
 * 		runs the game and takes care of destroying memory.
*******************************************************************************/

#include "spaces.hpp"
#include "dungeon.hpp"
#include "house.hpp"
#include "outside.hpp"
#include "character.hpp"
#include "menu.hpp"

#include <iostream>
#include <ctime>
int main()
{
	srand(time(NULL));
	Menu junkMenu(0);		     //Spaces( up, down, left, right, nameRoom, nameMonster);
	int intInput = -1;
	std::string input = "";
	srand(time(NULL));
	// Greet the use and tell them what the point of the game is
	std::cout << "\n\nYou have just awakened in a dark, damp, concrete hole. You vaguely "
		<< "\nremember being taken. You must escape! Be careful, there are "
		<< "\nmonsters in every room!!" << std::endl;

	Character *myPlayer = new Character;
	while(intInput == -1)
	{
		std::cout << "\nPress 1 to have " << myPlayer->getName()
			<< " leave the hole." << std::endl;
		std::cin.putback(' ');
		getline(std::cin, input);
		intInput = junkMenu.returnInt(input,1,1);
	}


/* Set up the linked spaces in the formation shown below
 *
 *		outside1
 *
 *		both go to outside1
 *	house2		house4
 *	house1		house3
 *		both go to house1
 *	dungeon2	dungeon4
 *	dungeon1	dungeon3
 *
 */
	//Set up all the spaces and the board pieces
	Spaces *dungeon1 = new Dungeon(nullptr, nullptr, nullptr, nullptr, "Dungeon 1", "Dracula");
	Spaces *dungeon2 = new Dungeon(nullptr, dungeon1, nullptr, nullptr, "Dungeon 2", "PennyWise");
	Spaces *dungeon3 = new Dungeon(nullptr, nullptr, dungeon1, nullptr, "Dungeon 3", "Leatherface");
	Spaces *dungeon4 = new Dungeon(nullptr, dungeon3, dungeon2, nullptr, "Dungeon 4", "Frankenstein");
	Spaces *house1 = new House(nullptr, dungeon4, nullptr, nullptr, "House 1", "Jason Voorhees");
	Spaces *house2 = new House(nullptr, house1, nullptr, nullptr, "House 2", "Michael Myers");
	Spaces *house3 = new House(nullptr, dungeon4, house1, nullptr, "House 3", "Norman Bates");
	Spaces *house4 = new House(nullptr, house3, house2, nullptr, "House 4", "Yourself");
	Spaces *outside1 = new Outside(nullptr, house4, nullptr, nullptr, "Outside", "Dragon");

	dungeon1->setUp(dungeon2);
	dungeon1->setRight(dungeon3);
	dungeon2->setRight(dungeon4);
	dungeon2->setUp(house1);
	dungeon3->setUp(dungeon4);
	dungeon4->setUp(house1);

	house1->setUp(house2);
	house1->setRight(house3);
	house2->setRight(house4);
	house2->setUp(outside1);
	house3->setUp(house4);
	house4->setUp(outside1);
	

	myPlayer->setSpace(dungeon1);
	std::cout << "\nYou found a satchel tied to the top of the hole."
		<< "\nIt might be useful later..." << std::endl;

	// play the game
	while(!outside1->getEnd() && !myPlayer->getDead())
	{
		myPlayer->attack();
		if(!myPlayer->getDead() && !outside1->getEnd())
		{
			myPlayer->optionsMenu(outside1);
		}
	}
	if(myPlayer->getDead())
	{
		std::cout << "You lost the fight to the monster. You have died." << std::endl;
	}
	// If the player has collected 4 pieces of metal they win, otherwise they lose
	else if(myPlayer->getSatchel() >= 4)
	{
		std::cout << "\nYou use your satchel to protect yourself, the strange metal "
			<< "inside turns into a key! It fits the front gate. You are free!"
			<< "\nCongratulations, you won the game." << std::endl;
	}
	else
	{
		std::cout << "Satchel: " << myPlayer->getSatchel() << std::endl;
		std::cout << "You use your satchel to protect yourself but it melts. "
			<< "\nYou are stuck forever in this horror movie. Goodbye."
			<<std::endl;
	}

	// Just delete everything
	delete dungeon1;
	delete dungeon2;
	delete dungeon3;
	delete dungeon4;
	delete house1;
	delete house2;
	delete house3;
	delete house4;
	delete outside1;
	delete myPlayer;

	return 0;
}
