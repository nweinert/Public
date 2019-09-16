/*******************************************************************************
* Program name: Command Line Hockey Simulator
* Author:	Nicholas Weinert
* Date:	9/16/2019
* Description:	Simple interface file for the Simulation class
*******************************************************************************/

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "team.hpp"

#include <string>
using std::string;

class Simulation{

	protected:
		int homeTeamGoals, awayTeamGoals;
		double homeMultiplier, awayMultiplier;
		Team *homeTeam;
		Team *awayTeam;
		Team *FreeAgents;

	public:
		Simulation(Team*, Team*, Team*);
		double getMultiplier(int);

		void setHomeMultiplier(double);
		void setAwayMultiplier(double);
		void setHomeGoals(int);
		void setAwayGoals(int);
		double getHomeMultiplier();
		double getAwayMultiplier();
		int getHomeGoals();
		int getAwayGoals();

		void runSim();
		void draftTeams();
		int scores(Team *, Team *, double, double);
		void printResults();

};
#endif
