/*******************************************************************************
* Program name: Command Line Hockey Simulator
* Author:	Nicholas Weinert
* Date:	9/16/2019
* Description:	This file implements the basic goalie class for the simulator.
*		This is a work in progress and needs updating to implement goalies
*		in the simulation.
*******************************************************************************/

#include "goalie.hpp"
#include <iostream>
#include <string>

// Base constructor for the Goalie class. Sets everything equal to 0
Goalie::Goalie() {

	setOffense(15);
	setDefense(70);
	setName("New Goalie");
	setType(4);
	setGoals(0);
	setAssists(0);
	setWins(0);
	setGaa(0.0);
}

// Alternate constructor for the Goalie class.
Goalie::Goalie(int offense, int defense, string name) {

	setOffense(offense);
	setDefense(defense);
	setName(name);
	setType(4);
	setGoals(0);
	setAssists(0);
	setWins(0);
	setGaa(0.0);
}

//Various getters and setters below
void Goalie::setWins(int newWins) {
	wins = newWins;
}

void Goalie::setGaa(double newGaa) {
	gaa = newGaa;
}

int Goalie::getWins() {
	return wins;
}

double Goalie::getGaa() {
	return gaa;
}

