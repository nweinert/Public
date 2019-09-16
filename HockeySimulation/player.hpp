/*******************************************************************************
* Program name: Command Line Hockey Simulator
* Author:	Nicholas Weinert
* Date:	9/16/2019
* Description:	Simple interface file for the Player class
*******************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
using std::string;

class Player{

	protected:
		int offense, defense, goals, assists;
		string name;
		enum playerType {OffensiveForward, DefensiveForward, OffensiveDefenseman, DefensiveDefensman, Goalie};
		playerType type;

	public:
		Player();
		Player(int offense, int defense, string name, int type);
		void setName(string);
		void setType(int);
		void setOffense(int);
		void setDefense(int);
		void setGoals(int);
		void setAssists(int);
		string getName();
		int getType();
		int getOffense();
		int getDefense();
		int getGoals();
		int getAssists();
		string printType(int);
};
#endif
