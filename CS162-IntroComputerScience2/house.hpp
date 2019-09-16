/*******************************************************************************
 * Program name:Final Project
 * Author:	Nicholas Weinert
 * Date:	12/02/2018
 * Description:	This is a header file containing the House class
 * 		The House class inherits from the abstract Spaces class
 * 		and overrides the doAttack function
*******************************************************************************/

#ifndef HOUSE_HPP
#define HOUSE_HPP

#include "spaces.hpp"

class House : public Spaces
{

	private:
	public:
		House();
		House(Spaces *upSpace, Spaces *downSpace, Spaces *leftSpace, Spaces *rightSpace, std::string nameRoom, std::string nameMonster);
		int doAttack(int);
};
#endif
