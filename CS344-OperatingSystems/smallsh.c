/******************************************************************************
 * Name: smallsh.c
 * Author: Nick Weinert (weinertn@oregonstate.edu)
 * Date: 7/29/2019
 * Description: smallsh implements a small shell program that mimics the basic
 * 	functionality of a bash shell using fork and exec calls to bash processes
******************************************************************************/
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>


//Using a mutex to lock and unlock background proccesses
pthread_mutex_t backgroundLock = PTHREAD_MUTEX_INITIALIZER;


/********************************************************************************
 * catchSIGINT is the signal catchig function used in the sigaction struct for
 * 	the sigint signal
 *
 * Preconditions: SIGINT passed into process
 * Postcondition: Process terminated with message about why
********************************************************************************/
void catchSIGINT(int signo) {

	char* message = "Process killed by signal 2\n";
	write(STDOUT_FILENO, message, 27);
}


/********************************************************************************
 * catchSIGSTP is the signal catching function used in the sigaction struct for
 * 	the signal SIGTSTP
 *
 * Preconditions: SIGTSTP passed into shell
 * Postcondition: Shell switches modes to allow or disallow the creation of 
 * 	background processes
********************************************************************************/
void catchSIGSTP(int signo) {

	int result = pthread_mutex_trylock(&backgroundLock);
	//if background lock is now locked (wasn't locked before)
	if (result == 0) {
		char* message = "Entering foreground-only mode (& is now ignored)\n";
		write(STDOUT_FILENO, message, 49);
	}
	//was locked before, need to unlock it to allow background proccesses
	else {
		pthread_mutex_unlock(&backgroundLock);
		char* message = "Exiting foreground-only mode (& is now allowed)\n";
		write(STDOUT_FILENO, message, 48);
	}
}


/********************************************************************************
 * setSignals sets the sigaction structs for the SIGINT and SIGTSTP
 * 	signals to handle them appropriately in the shell
 *
 * Preconditions: catchSIGINT and catchSIGSTP functions created
 * Postcondition: sigaction structs created and set up to appropriately handle 
 * 	SIGINT and SIGTSTP signals
********************************************************************************/
void initSignals() {
	struct sigaction intAction = {0}, stpAction = {0};
	intAction.sa_handler = catchSIGINT;
	sigfillset(&intAction.sa_mask);
	intAction.sa_flags = 0;
	stpAction.sa_handler = catchSIGSTP;
	sigfillset(&stpAction.sa_mask);
	stpAction.sa_flags = 0;

	sigaction(SIGINT, &intAction, NULL);
	sigaction(SIGTSTP, &stpAction, NULL);

}


/********************************************************************************
 * redirectIO redirects the input/output of the process as per user input
 *
 * Preconditions: User signaled the start of a process. Args have been parsed and numArgs
 * 	is known, background process command is known.
 * Postcondition: Output is redirected appropriately. Input and output are redirected 
 * 	to the user specified files, if any were specified. If a background process,
 * 	Input and output are redirected to dev/null. If no files were specified
 * 	for a foreground process, input and output remain at the terminal
********************************************************************************/
void redirectIO(int numArgs, int bg, char **args){

	//open dev/null for I/O redirection
	int devNull = open("/dev/null", O_RDWR);
	int newFile = 0;
	int result = 0;

	//if it is a backgrou process, redirect both input and output to dev/null
	if(bg == 1){
		dup2(devNull, 0);
		dup2(devNull, 1);

	}
	for(int i = 1; i < numArgs; i++){
		//if input file redirection
		if(strcmp(args[i], "<") == 0) {
			//open the specified file
			newFile = open(args[i + 1], O_RDONLY);
			//if it opened, redirect. If not, give error
			if(newFile >= 0){
				result = dup2(newFile, 0);
				args[i++] = NULL;
				args[i] = NULL;
			}
			else if (result == -1 || newFile < 0) {
				perror("Could not open INPUT file");
				exit(2);
			}
				
		}
		//Same logic as above for output redirection
		else if(strcmp(args[i], ">") == 0) {
			newFile = open(args[i + 1], O_WRONLY | O_CREAT, 0644);
			if(newFile >= 0){
				result = dup2(newFile, 1);
				args[i++] = NULL;
				args[i] = NULL;
			}
			else if(result == -1 || newFile < 0) {
				perror("Could not open OUTPUT file");
				exit(2);
			}
		}
	}


}


/********************************************************************************
 * getArgs parses the argument given by the user and stores them in an array of strings
 * 	it then returns the number of arguments.
 *
 * Preconditions: char** has been declared as an array of strings. Input has 
 * 	been gathered from the user.
 * Postcondition: each individual argument is stored in the args array
********************************************************************************/
int getArgs(char *input, char** args){

	char *arg = strtok(input, " ");
	int numArgs = 0;
	args[numArgs++] = arg;
	while(arg != NULL){
		arg = strtok(NULL, " ");
		args[numArgs++] = arg;
	}
	//clearing out newline character from the last arg
	args[numArgs - 2][strlen(args[numArgs - 2])- 1] = '\0';

	return numArgs - 1;
}


/********************************************************************************
 * expandArgs expands any '$$' in any arg into the process id of the shell
 *
 * Preconditions: getArgs has been run
 * Postcondition: '$$' is expanded into the pid of the shell in all arguments
********************************************************************************/
void expandArgs(char **args, int numArgs) {

	for(int i = 0; i < numArgs; i++){
		if(strstr(args[i], "$$") != NULL){
			//break argument into 3 pieces. Before $$, $$, and after $$
			char* arg1 = args[i];
			char* index = strstr(args[i], "$$");
			char arg2[100];
			memset(arg2, '\0', 100);
			strcpy(arg2, index + 2);
			//set $$ portion to 0 to clear out back part of argument
			*index = 0;

			char pid[16];
			memset(pid, '\0', 16);
			sprintf(pid, "%d", getpid());

			//concatenate first part, pid, and last part into new var
			char newArg[500];
			memset(newArg, '\0', 500);
			strcat(newArg, arg1);
			strcat(newArg, pid);
			strcat(newArg, arg2);
			//copy value of new var back into the argument
			strcpy(args[i], newArg);
		}
	}
}


/********************************************************************************
 * changeDir changes the current working directory of the shell
 *
 * Preconditions: getArgs has been run
 * Postcondition: CWD is changed to user passed dir, if the dir exists. If the 
 * 	user passes no dir the CWD is changed to the HOME dir
********************************************************************************/
void changeDir(char **args){
	int result = -5;

	//if no dir passed
	if(args[1] == NULL){
		result = chdir(getenv("HOME"));
	}
	else {
		result = chdir(args[1]);
	}

	//if it did not work
	if(result != 0){
		printf("That directory does not exist, please try again.");
	}
}


/********************************************************************************
 * getBG determines if the requested process should be started in the background.
 * 	It checks the background mutex and the last argument of the input string
 *
 * Preconditions: getArgs has been run, mutex created
 * Postcondition: Returns boolean value indicating whther the process can be 
 * 	started in the background
********************************************************************************/
int getBG(char **args, int *numArgs) {

	
	int bg = 0;
	//If the last arg is to command to start in background, set bg=1 and clear out last arg
	if(strcmp(args[*numArgs - 1], "&") == 0){
		bg = 1;
		args[--*numArgs] = NULL;
	}

	//if commaned to start in background, check mutex
	if(bg == 1){
		int result = pthread_mutex_trylock(&backgroundLock);

		//was unlocked - BG proccesses allowed
		if(result == 0){
			pthread_mutex_unlock(&backgroundLock);
		}
		// was locked - no BG proccesses allowed
		else {
			bg = 0;
		}
	}

	return bg;
}


/********************************************************************************
 * getStatus prints the status of the last completed child process
 *
 * Preconditions: INT holding the childExitMethod created and passed
 * Postcondition: Reason for last child termination printed to console
********************************************************************************/
void getStatus(int childExitMethod){
		
		if(WIFEXITED(childExitMethod) != 0){
			printf("Exit status: %d\n", WEXITSTATUS(childExitMethod)); fflush(stdout);
		} 
		else if(WIFSIGNALED(childExitMethod) != 0){
			printf("Terminated by signal: %d\n", WTERMSIG(childExitMethod)); fflush(stdout);
		}
}


/********************************************************************************
 * parseInput takes the user input and runs the appropriate function. It defines
 * 	functionality for the 3 built-in functions or returns the number of args
 * 	passed by a call to getArgs. It also calls expandArgs to expand any instances
 * 	of '$$'
 *
 * Preconditions: User input gathered, array of strings declared and passed, int holding
 * 	exitMethod of last child process passed.
 * Postcondition: If appropriate, 1 of the built in functions runs. Else, number of 
 * 	arguments passed is returned.
********************************************************************************/
int parseInput(char *input, char **args, int childExitMethod){

	if(input[0] == '#' || input[0] == '\n'){
		return 0;
	}

	int numArgs = getArgs(input, args);
	expandArgs(args, numArgs);

	if(strcmp(args[0], "exit") == 0) {
		return -1;
	}
	else if(strcmp(args[0], "cd") == 0){
		changeDir(args);
		return 0;
	}
	else if(strcmp(args[0], "status") == 0){
		getStatus(childExitMethod);
		return 0;
	}
	else {
		return numArgs;
	}

}


/********************************************************************************
 * killKids sends a kill signal to each child process
 *
 * Preconditions: Array of children process ID's is passed and number of children
 * 	is known and passed
 * Postcondition: All child processes are terminated
********************************************************************************/
void killKids(pid_t *childArray, int numChildren){

	for(int i = 0; i < numChildren; i++){
		kill(childArray[i], 15);
	}
}


/********************************************************************************
 * reapChildren looks for defunct zombie child processes and cleans them up.
 * 	It prints a message telling which process ID's it cleaned and the reason
 * 	for that process termination. Returns the new number of children
 *
 * Preconditions: Array of children process ID's is passed and number of children
 * 	is known and passed, int to hold exitMethod of last child passed
 * Postcondition: Zombie proccess managed and information output to console 
********************************************************************************/
int reapChildren(pid_t *childArray, int *childExitMethod, int numChildren){

	int temp = numChildren;	
	//for each child
	for(int i = 0; i < numChildren; i++){
		//hold tempId
		pid_t tempId = childArray[i];
		//if it finds a zombie process, clean it up
		if(waitpid(childArray[i], childExitMethod, WNOHANG) != 0) {
			printf("Background process ID: %d has terminated\n", tempId);
			getStatus(*childExitMethod);
			temp--;
			//maintain array of childrenID's with no holes
			for(int j = 0; j < numChildren; j++){
				childArray[j] = childArray[j + 1];
			}
		}
	}
	return temp;

}

int main() {


	//Initialize the signal handlers
	initSignals();
	//setting up a block on SIGINT so it can only be run while a foreground process runs
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigprocmask(SIG_BLOCK, &mask, NULL);

	//initialize various necessary vars
	int result = 0;
	int childExitMethod = -5;
	pid_t spawnid = -5;
	pid_t childArray[500];
	int numChildren = 0;
	memset(childArray, 0, 500);
	char *args[512];

	//result is only < 0 is user types exit command
	while(result >= 0){
		//clean up the zombies
		numChildren = reapChildren(childArray, &childExitMethod, numChildren);
		printf(":"); fflush(stdout);

		//get user input
		int numCharsEntered = -5;
		size_t bufferSize = 0;
		char *command = NULL;
		memset(args, 0, 512 * sizeof(char *));
		result = 0;

		numCharsEntered = getline(&command, &bufferSize, stdin);
		if(numCharsEntered == -1){
			clearerr(stdin);
		}
		else {
			result = parseInput(command, args, childExitMethod);
		}

		//If the command was not for one of the built in functions, result will be at least 1
		//all built in functions return 0 or -1
		if(result >= 1) {
			//figure out if it is a background process request
			int bg = getBG(args, &result);
			spawnid = fork();
			switch(spawnid) {
				case -1: 
					perror("Uh oh...spawnID");
					exit(1);
				case 0:	
					//print info, redirect I/O and exec into bash function
					if(bg == 1){
						printf("Background pid is %d\n", getpid());
					}
					redirectIO(result, bg, args);
					if(execvp(*args, args) < 0){
						perror("Uh oh...exec");
						exit(1);
					}
				default:
					//wait for the foreground process to finish
					if(!bg) {
						//unblock SIGINT
						sigprocmask(SIG_UNBLOCK, &mask, NULL);
						waitpid(spawnid, &childExitMethod, 0);
					}
					//store background process id in array of child pid's
					else {
						childArray[numChildren] = spawnid;
						numChildren++;
					}
			}
		}
		free(command);
	
	}
	//clean the kids
	killKids(childArray, numChildren);
	return 0;
}
