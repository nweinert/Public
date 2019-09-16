/*******************************************************************************
* Program name: Command Line Hockey Simulator
* Author:	Nicholas Weinert
* Date:	9/16/2019
* Description:	This file implements the basic Team class for the simulator.
*		Teams consist of objects from the Player class.
*******************************************************************************/

#include "goalie.hpp"
#include "player.hpp"
#include "team.hpp"
#include <iostream>
#include <string>
#include <fstream>

// Base constructor for the Team class. Sets everything equal to 0
Team::Team() {
	setNumPlayers(0);
	setOffense();
	setDefense();
	setName("New Team");
	for(int i = 0; i < 500; i++) {
		players[i] = nullptr;
	}
	goalie = nullptr;
}

// Alternate constructor for the Team class. Sets team name to name passed
Team::Team(string name) {
	setNumPlayers(0);
	setOffense();
	setDefense();
	setName(name);
	for(int i = 0; i < 500; i++) {
		players[i] = nullptr;
	}
	goalie = nullptr;
}

// Destructor for team class, removes and destroys all players and goalies
Team::~Team() {

	for(int i = 0; i < getNumPlayers(); i++) {
		delete(players[i]);
		players[i] = nullptr;
	}
	if(goalie != nullptr) {
		delete(goalie);
		goalie = nullptr;
	}
}

/*********************************************************************************
* addPlayer takes a Player adds it to the current team
* Preconditions: Player exists and is passed
* Postconditions: Passed Player added to the team if room
**********************************************************************************/
void Team::addPlayer(Player *newPlayer) {

	if(getNumPlayers() < 5 || getName().compare("Free Agents") == 0) {
		players[getNumPlayers()] = newPlayer;
		setNumPlayers(getNumPlayers() + 1);
	}
	else {
		std::cout << "Team is full. Delete a player first" << std::endl;
	}
}

/*********************************************************************************
* addGoalie takes a Goalie from the FreeAgents team and moves it to the current team
* Preconditions: Goalie exists and is passed
* Postconditions: Passed Goalie added to the team
**********************************************************************************/
void Team::addGoalie(Goalie *newGoalie) {

	if(goalie != nullptr) {
		delete(goalie);
		goalie = nullptr;
	}
	goalie = newGoalie;
}

/*********************************************************************************
* removePlayer simply removes a player from the team and shuffles the current team
* to avoid holes in the array of Players. 
* Preconditions: Passed index is positive
* Postconditions: Team no longer contains Player that existed at the index
**********************************************************************************/
void Team::removePlayer(int index) {

	for (int i = index; i < getNumPlayers(); i++) {
		players[i] = players[i + 1];
		players[i + 1] = nullptr;
	}
	setNumPlayers(getNumPlayers() - 1);
}

/*********************************************************************************
* deletePlayer deletes a player from the team
* Preconditions: Passed index is positive
* Postconditions: Player that existed at the index no longer exists
**********************************************************************************/
void Team::deletePlayer(int index) {

	delete(players[index]);
	removePlayer(index);
}

/*********************************************************************************
* createPlayer allows the user to create a custom Player with all Player attributes.
* It calls the Player constructor and adds the player to the team.
* Preconditions: Integers for offense and defense are positive and passed, name is valid string
*	type is valid integer in range 0-4
* Postconditions: New Player created and added to the team, if there is room on the team
**********************************************************************************/
void Team::createPlayer(int offense, int defense, string name, int type) {

	if(type == 4) {
		if(goalie == nullptr) {
			goalie = new Goalie(offense, defense, name);
		}
		else {
			delete(goalie);
			goalie = nullptr;
			goalie = new Goalie(offense, defense, name);
		}
	}
	else {
		if (getNumPlayers() < 5 || getName().compare("Free Agents") == 0) {
			players[getNumPlayers()] = new Player(offense, defense, name, type);
			setNumPlayers(getNumPlayers() + 1);
		}
		else {
			std::cout << "Team is full. Delete a player first" << std::endl;
		}
	}
}

/*********************************************************************************
* assignPoints assigns points in a psuedo-random way while taking into account proportions
* of offense each player brings to the team
* Preconditions: Team exists and is full of players
* Postconditions: Players are assigned goal and assist(s) for 1 goal
**********************************************************************************/
void Team::assignPoints() {

	const int size = getNumPlayers();
	int *temp = new int[size];

	for (int i = 0; i < size; i++) {
		if (i == 0) {
			temp[i] = players[i]->getOffense() + getNumPlayers();
		}
		else {
			temp[i] = players[i]->getOffense() + temp[i - 1];
		}
	}

	int goal = ((rand() * 1000) % getOffense()) + getNumPlayers();
	int assist1 = ((rand() * 1000) % getOffense()) + getNumPlayers();
	int assist2 = ((rand() * 1000) % getOffense()) + getNumPlayers();

	//assign the goal
	for (int i = 0; i < getNumPlayers(); i++) {
		if (i == 0) {
			if (goal <= temp[i] && goal > getNumPlayers()) {
				players[i]->setGoals(players[i]->getGoals() + 1);
				goal = i;
			}
		}
		else {
			if (goal <= temp[i] && goal > temp[i - 1]) {
				players[i]->setGoals(players[i]->getGoals() + 1);
				goal = i;
			}
		}
	}

	//assign the assists in the same way. Player can't get two assists on the same goal 
	//or an assist on his own goal. If that's the way it shakes out, nobody gets the assist
	for (int i = 0; i < getNumPlayers(); i++) {
		if (i == 0) {
			if (assist1 <= temp[i] && assist1 > getNumPlayers() && goal != i) {
				players[i]->setAssists(players[i]->getGoals() + 1);
				assist1 = i;
			}
		}
		else {
			if (assist1 <= temp[i] && assist1 > temp[i - 1] && goal != i) {
				players[i]->setAssists(players[i]->getGoals() + 1);
				assist1 = i;
			}
		}
	}

	for (int i = 0; i < getNumPlayers(); i++) {
		if (i == 0) {
			if (assist2 <= temp[i] && assist2 > getNumPlayers() && goal != i && assist1 != i) {
				players[i]->setAssists(players[i]->getGoals() + 1);
				assist2 = i;
			}
		}
		else {
			if (assist2 <= temp[i] && assist2 > temp[i - 1] && goal != i && assist1 != i) {
				players[i]->setAssists(players[i]->getGoals() + 1);
				assist2 = i;
			}
		}
	}

}

/*********************************************************************************
* getFA gets, sorts, and prints the FreeAgents team list
* Preconditions: FreeAgents team is created and filled
* Postconditions: Printed list of possible FreeAgents
**********************************************************************************/
void Team::getFA(Team *FreeAgents) {

	std::cout << "Would you like to sort the available players? \n0.\tSort by Offense\n1.\tSort by Defense\n2.\tNo Sort" << std::endl;
	string str;

	getline(std::cin, str);
	int choice = stoi(str);

	if (choice != 2) {
		FreeAgents->sort(choice);
	}

	for (int i = 0; i < FreeAgents->getNumPlayers(); i++) {
		std::cout << FreeAgents->players[i]->getName() << "\tOffense: " <<
			FreeAgents->players[i]->getOffense() << "\tDefense: " <<
			FreeAgents->players[i]->getDefense() << std::endl;
	}

}

/*********************************************************************************
* randomTeam randomly assigns 5 players to the team from the FreeAgents list
* Preconditions: Team created and initialized, FreeAgents team created and filled
* Postconditions: Team contains 5 random players
**********************************************************************************/
void Team::randomTeam(Team *FreeAgents) {

	while (getNumPlayers() < 5) {
		int totalPlayers = FreeAgents->getNumPlayers();

		int index = rand() % totalPlayers;
		addPlayer(FreeAgents->players[index]);
		FreeAgents->removePlayer(index);
	}
}

/*********************************************************************************
* draftPlayer allows the user to choose a player from the FreeAgents list and add it 
* to the team
* Preconditions: 2 Teams created and initialized, FreeAgents team created and filled
* Postconditions: 2 teams have 5 players each
**********************************************************************************/
void Team::draftPlayer(Team *FreeAgents) {

	std::cout << "\nPlease make a selection for " << getName() << "'s roster." << std::endl;
	bool realPlayer = false;

	while (realPlayer == false) {
		getFA(FreeAgents);
		std::cout << "\nEnter a full name to draft a player." << std::endl;
		string name;
		getline(std::cin, name);
		for (int i = 0; i < FreeAgents->getNumPlayers(); i++) {
			if (name.compare(FreeAgents->players[i]->getName()) == 0) {
				addPlayer(FreeAgents->players[i]);
				FreeAgents->removePlayer(i);
				printStats();
				realPlayer = true;
			}
		}
		if (realPlayer == false) {
			std::cout << "That player is not in the game or their name is spelled incorrectly. Please try again." << std::endl;
		}
	}
}

/*********************************************************************************
* printStats prints goals, assists and other important stats for each player
* on the team to the console for user viewing
* Preconditions: Team is created and filled with players
* Postconditions: Player stats are printed to console
**********************************************************************************/
void Team::printStats() {

	std::cout << "Players for " << getName() << ": " << getNumPlayers() << std::endl;
	for (int i = 0; i < getNumPlayers(); i++) {
		std::cout << players[i]->getName() << ":\n\tGoals:\t\t" << players[i]->getGoals()
			<< "\n\tAssists:\t" << players[i]->getAssists() << "\n\tOffense:\t"
			<< players[i]->getOffense() << "\n\tDefense:\t" << players[i]->getDefense()
			<< "\n\tType:\t\t" << players[i]->printType(players[i]->getType()) << std::endl;
	}

	if (goalie != nullptr) {
		std::cout << goalie->getName() << ":\n\tGoals:\t\t" << goalie->getGoals()
			<< "\n\tAssists:\t" << goalie->getAssists() << "\n\tGAA:\t\t"
			<< goalie->getGaa() << "\n\tWins:\t\t" << goalie->getWins()
			<< "\n\tOffense:\t" << goalie->getOffense() << "\n\tDefense:\t"
			<< goalie->getDefense() << std::endl;
	}

}

/*********************************************************************************
* makeFA creates the FreeAgents team from the csv file that contains all the players.
* Preconditions: CSV file skaterList.csv exists in proper format with player ratings 
* Postconditions: Team is filled with skaters from the file
**********************************************************************************/
void Team::makeFA() {

	int offense = 0, defense = 0, type = 0;;
	string str, name;
	std::ifstream myFile;
	myFile.open("skaterList.csv");
	while (getline(myFile, str, ',')) {
		if (!str.empty()) {
			name = str;
			getline(myFile, str, ',');
			offense = stoi(str);
			getline(myFile, str, ',');
			defense = stoi(str);
			getline(myFile, str, '\n');
			type = stoi(str);
			createPlayer(offense, defense, name, type);
		}
	}
	myFile.close();
}

// Various getters and setters
int Team::getNumPlayers() {
	return numPlayers;
}

void Team::setNumPlayers(int newNum) {
	numPlayers = newNum;
}

void Team::setOffense() {

	totalOffense = 0;
	for(int i = 0; i < getNumPlayers(); i++) {
		totalOffense += players[i]->getOffense();
	}
}

void Team::setDefense() {

	totalDefense = 0;	
	for(int i = 0; i < getNumPlayers(); i++) {
		totalDefense += players[i]->getDefense();
	}
}

int Team::getOffense() {
	setOffense();
	return totalOffense;
}

int Team::getDefense() {
	setDefense();
	return totalDefense;
}

string Team::getName() {
	return name;
}

void Team::setName(string newName) {
	name = newName;
}

//Below are functions for sorting the players. Mergesort is used

void Team::merge(Player *a[], int low, int high, int mid, int type)
{
	// We have low to mid and mid+1 to high already sorted.
	const int size = high - low + 1;
	Player **temp = new Player *[size];
	int i, j, k;
	i = low;
	k = 0;
	j = mid + 1;

	int holder1 = 0, holder2 = 0;


	// Merge the two parts into temp[].
	while (i <= mid && j <= high && a[i] != nullptr && a[j] != nullptr)
	{
		//Sort offense
		if (type == 0) {
			holder1 = a[i]->getOffense();
			holder2 = a[j]->getOffense();
		}
		else { //sort defense
			holder1 = a[i]->getDefense();
			holder2 = a[j]->getDefense();
		}
		if (holder1 < holder2)
		{
			temp[k] = a[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = a[j];
			k++;
			j++;
		}
	}

	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
		temp[k] = a[i];
		k++;
		i++;
	}

	// Insert all the remaining values from j to high into temp[].
	while (j <= high)
	{
		temp[k] = a[j];
		k++;
		j++;
	}


	// Assign sorted data stored in temp[] to a[].
	for (i = low; i <= high; i++)
	{
		a[i] = temp[i - low];
	}
}

// A function to split array into two parts.
void Team::mergeSort(Player *a[], int low, int high, int type)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		// Split the data into two half.
		mergeSort(a, low, mid, type);
		mergeSort(a, mid + 1, high, type);

		// Merge them to get sorted output.
		merge(a, low, high, mid, type);
	}
}

void Team::sort(int offDef) {
	mergeSort(this->players, 0, this->numPlayers, offDef);
}
