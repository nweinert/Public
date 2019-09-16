/*******************************************************************************
 * Program name:Final Project
 * Author:	Nicholas Weinert
 * Date:	12/02/2018
 * Description:	This is an implementation file containing the Spaces class
 * 		The Spaces class is pure virtual and is overridden by each 
 * 		child class. It defines variables and getters and setters
 * 		for the variables
*******************************************************************************/

#ifndef SPACES_HPP
#define SPACES_HPP

#include <string>

class Spaces
{

        protected:
                Spaces *up;
                Spaces *down;
                Spaces *left;
                Spaces *right;
		std::string spaceName;
		std::string monster;
		bool beenSearched, beenCleared;
		bool end;

       public:
                Spaces();
		Spaces(Spaces *, Spaces *, Spaces *, Spaces *, std::string, std::string);
                virtual int doAttack(int)=0;

		void setUp(Spaces *);
		void setDown(Spaces *);
		void setLeft(Spaces *);
		void setRight(Spaces *);
		Spaces * getUp();
		Spaces * getDown();
		Spaces * getLeft();
		Spaces * getRight();
                std::string getName();
                void setName(std::string);
                std::string getMonster();
                void setMonster(std::string);
		bool getSearched();
		void setSearched(bool);
		bool getCleared();
		void setCleared(bool);
		bool getEnd();
		void setEnd(bool);
		void printMap();
};
#endif
