/*******************************************************************************
* Program name: Command Line Hockey Simulator
* Author:	Nicholas Weinert
* Date:	9/16/2019
* Description:	Simple interface file for the Team class
*******************************************************************************/

#ifndef TEAM_HPP
#define TEAM_HPP

#include <string>
using std::string;

class Team{

	protected:
		int totalOffense, totalDefense, numPlayers;
		string name;
		Player *players[500];
		Goalie *goalie;

	public:
		Team();
		Team(string name);
		void addPlayer(Player *);
		void addGoalie(Goalie *);
		void deletePlayer(int);
		void removePlayer(int);
		void createPlayer(int offense, int defense, string name, int type);
		void setOffense();
		void setDefense();
		void setNumPlayers(int);
		void setName(string);
		int getOffense();
		int getDefense();
		int getNumPlayers();
		string getName();

		void assignPoints();
		void randomTeam(Team *FreeAgents);
		void draftPlayer(Team *FreeAgents);
		void getFA(Team *FreeAgents);
		void printStats();
		void makeFA();

		void sort(int type);
		void merge(Player *[], int, int, int, int);
		void mergeSort(Player *[], int, int, int);

		~Team();



};
#endif
