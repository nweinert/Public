/*******************************************************************************
* Program name: Command Line Hockey Simulator
* Author:	Nicholas Weinert
* Date:	9/16/2019
* Description:	Simple interface file for the Goalie class
*******************************************************************************/

#ifndef GOALIE_HPP
#define GOALIE_HPP

#include "player.hpp"

class Goalie : public Player{

	protected:
		int wins;
		double gaa;

	public:
		Goalie();
		Goalie(int offense, int defense, string name);
		void setWins(int);
		void setGaa(double);
		int getWins();
		double getGaa();
};
#endif
