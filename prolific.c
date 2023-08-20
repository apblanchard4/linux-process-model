#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char  *argv[]) {

FILE *seed = fopen(argv[1], "r");//Reads the seed file.
char fileString[255]; //create string space for seed file read, dummy number
fgets(fileString, 255, seed); //get the first line,store it in fileString 

int seedNum = atoi(fileString); //change the string in the file to be an int
printf("Seed value: %d\n", seedNum);  //print the seed number
srand(seedNum); //seeds the random number generator

int childNum= (rand()%6 +5); //Create a random number for number of child
int arrRandNum[childNum]; //creates an array with the number of children
printf("Number of children: %d\n", childNum);

for (int i=0; i<childNum; i++) { //go through number of children
	int randNum = rand(); //create random num
	arrRandNum[i] = randNum; //put rand num into array position
	}

int counter=0;
while (counter < childNum) { //go through one iteration per child
	int pid = fork();  //fork the num of children, go into loop if child
	if (pid < 0) { //fork failed,
		fprintf(stderr, "fork failed\n");
	}
	int myRand = arrRandNum[counter]; //get their random num
        int exitcode = ((myRand % 50) +1); //get exit code
        int time = ((myRand % 3) + 1); //get wait time
	
	if (pid == 0) { //child	
		wait(); //wait for parent statement
		printf("[Child, PID: %d]: I am the child and I will wait %d seconds and exit with code %d\n",getpid() ,time, exitcode ); 
		sleep(time);  //wait for designated time
		printf("[Child, PID: %d]: Now exiting\n",getpid());
		exit(exitcode);
	}
	else { //parent
		printf("[Parent]: I am waiting for PID %d to finish\n",pid );
		waitpid(pid); //wait on current child to finish before exit
		printf("[Parent]: Child %d finished with status code %d\n", pid,exitcode ); 
	}

counter++; //add to child counter
}
exit (0);
}


