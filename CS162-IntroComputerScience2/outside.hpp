/*******************************************************************************
 * Program name:Final Project
 * Author:	Nicholas Weinert
 * Date:	12/02/2018
 * Description:	This is a header file containing the Outside class
 * 		The Outside class inherits from the abstract Spaces class
 * 		and overrides the doAttack function
*******************************************************************************/

#ifndef OUTSIDE_HPP
#define OUTSIDE_HPP

#include "spaces.hpp"

class Outside : public Spaces
{

	private:
		bool end;
	public:
		Outside();
		Outside(Spaces *upSpace, Spaces *downSpace, Spaces *leftSpace, Spaces *rightSpace, std::string nameRoom, std::string nameMonster);
		int doAttack(int);
};

#endif
