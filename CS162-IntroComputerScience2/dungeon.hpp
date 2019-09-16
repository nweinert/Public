/*******************************************************************************
 * Program name:Final Project
 * Author:	Nicholas Weinert
 * Date:	12/02/2018
 * Description:	This is an header file containing the Dungeon class
 * 		The Dungeon Class inherits from the abstract Spaces class
 * 		and overrides the doAttack function
*******************************************************************************/

#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include "spaces.hpp"

class Dungeon : public Spaces
{

	private:
	public:
		Dungeon();
		Dungeon(Spaces *upSpace, Spaces *downSpace, Spaces *leftSpace, Spaces *rightSpace, std::string nameRoom, std::string nameMonster);
		int doAttack(int);
};
#endif
