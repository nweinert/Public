/*******************************************************************************
* Program name: Command Line Hockey Simulator
* Author:	Nicholas Weinert
* Date:	9/16/2019
* Description:	This file implements the basic Player class for the simulator.
*		The attributes passed in are based off of a csv file manioulated outside the program.
*		Eventually I would like to make those manipulations happen inside the program
*		itself.
*******************************************************************************/

#include "player.hpp"
#include <iostream>
#include <string>

// Base constructor for the Player class. Sets everything equal to 0
Player::Player() {

	setOffense(50);
	setDefense(50);
	setName("New Player");
	setType(3);
	setGoals(0);
	setAssists(0);
}

// Alternate constructor for the Player class.
Player::Player(int offense, int defense, string name, int type) {

	setOffense(offense);
	setDefense(defense);
	setName(name);
	setType(type);
	setGoals(0);
	setAssists(0);
}

//Various getters and setters below
void Player::setName(string newName) {
	name = newName;
}

void Player::setType(int newType) {
	type = static_cast<playerType>(newType);
}

void Player::setOffense(int rating) {
	offense = rating;
}

void Player::setDefense(int rating) {
	defense = rating;
}

void Player::setGoals(int newGoals) {
	goals = newGoals;
}

void Player::setAssists(int newAssists) {
	assists = newAssists;
}

string Player::getName() {
	return name;
}

int Player::getType() {
	return static_cast<int>(type);
}

int Player::getOffense() {
	return offense;
}

int Player::getDefense() {
	return defense;
}

int Player::getGoals() {
	return goals;
}

int Player::getAssists() {
	return assists;
}

string Player::printType(int type) {

	switch (type) {
		case 0:
			return "Offensive Forward";
		case 1:
			return "Defensive Forward";
		case 2:
			return "Offensive Defenseman";
		case 3:
			return "Defensive Defenseman";
		case 4:
			return "Goalie";
		default:
			return "Player Type Undefined";
	}
}
