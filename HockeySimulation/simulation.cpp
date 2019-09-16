/*******************************************************************************
* Program name: Command Line Hockey Simulator
* Author:	Nicholas Weinert
* Date:	9/16/2019
* Description:	This file implements the simulation class for the simulator.
*		These variables are a work in progress and may need updating to more 
*		accurately reflect realistic hockey outcomes.
*******************************************************************************/

#include "goalie.hpp"
#include "player.hpp"
#include "team.hpp"
#include "simulation.hpp"
#include <iostream>
#include <string>

//No base constructor for simulation. Replaced with the below constructor
Simulation::Simulation(Team *home, Team *away, Team *freeAgents) {

	homeTeam = home;
	awayTeam = away;
	FreeAgents = freeAgents;
	setHomeGoals(0);
	setAwayGoals(0);
	setHomeMultiplier(getMultiplier(0));
	setAwayMultiplier(getMultiplier(1));
}

/*********************************************************************************
* getMultiplier simply returns a random double to be used as a multiplier for the 
* passed team
* Preconditions: Team is created and initialized, integer passed for home or away
* Postconditions: Random multiplier is returned
**********************************************************************************/
double Simulation::getMultiplier(int team) {

	double mult = 0.0;
	int temp = (rand() % 50) + 70;

	//if home team
	if (team == 0) {
		mult = static_cast<double>(temp + 5) / 100.0;
	}
	else {
		mult = static_cast<double>(temp) / 100.0;
	}
	return mult;
}

/*********************************************************************************
* draftTeams cycles alternates between the two teams allowing the user to draft players.
* this continues until each team has 5 players
* Preconditions: Simulation is initialized, FreeAgents list is initialized
* Postconditions: Teams contain 5 players each
**********************************************************************************/
void Simulation::draftTeams() {

	while (homeTeam->getNumPlayers() < 5 && awayTeam->getNumPlayers() < 5) {
		int numHomePlayers = homeTeam->getNumPlayers(), numAwayPlayers = awayTeam->getNumPlayers();
		//As soon as a player is validly drafted this while loop will exit
		while (homeTeam->getNumPlayers() <= numHomePlayers) {
			homeTeam->draftPlayer(FreeAgents);
		}
		while (awayTeam->getNumPlayers() <= numAwayPlayers) {
			awayTeam->draftPlayer(FreeAgents);
		}
	}
}

/*********************************************************************************
* scores determines the number of goals scored by the offensive team, and calls 
* assign points to assign the goals and assists to the players on the scoring team.
* Preconditions: Simulation initialized, both teams contain 5 players each, multipliers 
*			exist and are passed
* Postconditions: Points are assigned to the players of the offensive team, number of
*			goals scored is returned
**********************************************************************************/
int Simulation::scores(Team *oTeam, Team *dTeam, double oMultiplier, double dMultiplier) {

	double totalO = (oTeam->getOffense() * oMultiplier), totalD = (dTeam->getDefense() * dMultiplier);

	int result = (totalO - totalD) / 3;
	int goals = 0;

	if (result >= 10) {
		goals = rand() % 9;
	}
	else if (result >= 4) {
		goals = rand() % 7;
	}
	else if (result >= 0) {
		goals = rand() % 5;
	}
	else if (result >= -4) {
		goals = rand() % 4;
	}
	else {
		goals = rand() % 3;
	}

	for (int i = 0; i < goals; i++) {
		oTeam->assignPoints();
	}

	return goals;
}

/*********************************************************************************
* runSim runs the simulation, calculating the number of goals scored for each team in 
* each of 3 periods and printing the results.
* Preconditions: Simulation is initialized, teams are created and full
* Postconditions: 1 game simulation is completed
**********************************************************************************/
void Simulation::runSim() {

	setHomeGoals(0);
	setAwayGoals(0);

	for (int period = 0; period < 3; period++) {
		setHomeGoals(getHomeGoals() + scores(homeTeam, awayTeam, getHomeMultiplier(), getAwayMultiplier()));
		setAwayGoals(getAwayGoals() + scores(awayTeam, homeTeam, getAwayMultiplier(), getHomeMultiplier()));
	}
	printResults();
}

/*********************************************************************************
* printResults determines the winner and informs the user of the winner and score
* Preconditions: >= 1 game simulation has been completed
* Postconditions: Results of simulation are printed to the console.
**********************************************************************************/
void Simulation::printResults() {

	std::cout << "Score:\n\t" << homeTeam->getName() << ": " << getHomeGoals() << "\n\t" <<
		awayTeam->getName() << ": " << getAwayGoals() << std::endl;
	if (getHomeGoals() > getAwayGoals()) {
		std::cout << homeTeam->getName() << " win!" << std::endl;
	}
	else if (getHomeGoals() < getAwayGoals()) {
		std::cout << awayTeam->getName() << " win!" << std::endl;
	}
	else {
		std::cout << "It's a tie!" << std::endl;
	}
}

//Various getters and setters below
void Simulation::setHomeMultiplier(double multiplier) {
	homeMultiplier = multiplier;
}

void Simulation::setAwayMultiplier(double multiplier) {
	awayMultiplier = multiplier;
}

void Simulation::setHomeGoals(int newGoals) {
	homeTeamGoals = newGoals;
}

void Simulation::setAwayGoals(int newGoals) {
	awayTeamGoals = newGoals;
}

int Simulation::getHomeGoals() {
	return homeTeamGoals;
}

int Simulation::getAwayGoals() {
	return awayTeamGoals;
}

double Simulation::getHomeMultiplier() {
	return homeMultiplier;
}

double Simulation::getAwayMultiplier() {
	return awayMultiplier;
}

