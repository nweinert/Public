/*******************************************************************************
 * Program name:Final Project
 * Author:	Nicholas Weinert
 * Date:	12/02/2018
 * Description:	This is an implementation file containing the Spaces class
 * 		The Spaces class is pure virtual and is overridden by each 
 * 		child class. It defines variables and getters and setters
 * 		for the variables
*******************************************************************************/

#include "spaces.hpp"
#include "menu.hpp"
#include "character.hpp"
#include <iostream>

// Spaces default constructor just sets everything to null
Spaces::Spaces()
{
        setName("Null Room");
        up = nullptr;
        down = nullptr;
        left = nullptr;
        right = nullptr;
        setMonster("Null Monster");
	setSearched(false);
	setCleared(false);
}
// Spaces default constructor sets everything to passed parameters
Spaces::Spaces(Spaces *upSpace, Spaces *downSpace, Spaces *leftSpace, Spaces *rightSpace, 
	std::string nameRoom, std::string nameMonster)
{
        setName(nameRoom);
        setMonster(nameMonster);
        up = upSpace;
        down = downSpace;
        left = leftSpace;
        right = rightSpace;
	setSearched(false);
	setCleared(false);
}

/************************************************************************************
 * The doAttack function is the ine that makes this class purely virtual. It gets
 * overridden by all child classes so it does nothing here.
************************************************************************************/
int Spaces::doAttack(int)
{
}

/************************************************************************************
 * printMap Prints a static map that is applicable for this version of the game only
 * I did not have time to come up with something better that would always work
************************************************************************************/
void Spaces::printMap()
{
	std::cout << "\tOutside\nHouse 2\t\tHouse 4\nHouse 1\t\tHouse 3" << std::endl;
	std::cout << "Dungeon 2\tDungeon 4\nDungeon 1\tDungeon 3\n\tHole" << std::endl;
}

/************************************************************************************
 * The following are simply getters and setters for the variables
*************************************************************************************/
bool Spaces::getEnd()
{
	return end;
}

void Spaces::setEnd(bool newEnd)
{
	end = newEnd;
}

bool Spaces::getSearched()
{
	return beenSearched;
}

void Spaces::setSearched(bool trueFalse)
{
	beenSearched = trueFalse;
}

bool Spaces::getCleared()
{
	return beenCleared;
}

void Spaces::setCleared(bool trueFalse)
{
	beenCleared = trueFalse;
}

void Spaces::setUp(Spaces *newSpace)
{
	up = newSpace;
}
void Spaces::setDown(Spaces *newSpace)
{
	down = newSpace;
}
void Spaces::setLeft(Spaces *newSpace)
{
	left = newSpace;
}
void Spaces::setRight(Spaces *newSpace)
{
	right = newSpace;
}

Spaces * Spaces::getUp()
{
	return up;
}
Spaces * Spaces::getDown()
{
	return down;
}
Spaces * Spaces::getLeft()
{
	return left;
}
Spaces * Spaces::getRight()
{
	return right;
}

std::string Spaces::getName()
{
        return spaceName;
}

void Spaces::setName(std::string name)
{
        spaceName = name;
}

void Spaces::setMonster(std::string name)
{
        monster = name;
}

std::string Spaces::getMonster()
{
        return monster;
}
