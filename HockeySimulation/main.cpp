/*******************************************************************************
 * Program name: Command Line Hockey Simulator
 * Author:	Nicholas Weinert
 * Date:	9/16/2019
 * Description:	This program simulates 3-on-3 hockey games using current NHL
 *		and is based on their performance in the NHL.
*******************************************************************************/

#include "player.hpp"
#include "goalie.hpp"
#include "team.hpp"
#include "simulation.hpp"
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>

using std::cout;
using std::endl;

int main() {
	srand(time(NULL));

	Team *FreeAgents = new Team("Free Agents");
	FreeAgents->makeFA();

	Team *wings = new Team("Detroit Red Wings");
	Team *avs = new Team("Colorado Avalanche");
	//wings->randomTeam(FreeAgents);
	//avs->randomTeam(FreeAgents);
	Simulation mySim = Simulation(wings, avs, FreeAgents);
	mySim.draftTeams();
	for (int i = 0; i < 10; i++) {
		mySim.runSim();
	}


	wings->printStats();
	avs->printStats();




	delete(FreeAgents);
	return 0;
}
