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

int lifespan= (rand()%6 +8); //Create a random number for life span
printf("Random Descendant Count: %d\n Time to meet the kids/grandkids/great grandkids\n ", lifespan);

while (lifespan > 0) {
	int pid = fork(); //create child
	int exitcode = 0;
 	if (pid < 0) { //failed fork
		fprintf(stderr, "fork failed\n");
		}
		
		
	if (pid == 0) { //child	
		sleep(1); //wait for parent statement
		printf("[Child, PID: %d]: I was called with descendant count =%d. I'll have %d descendants\n",getpid() ,lifespan, lifespan-1); 
		exitcode++;	

	}
	else { //parent
		printf("[Parent, PID: %d]: I am waiting for %d to finish\n", getpid(), pid );
		wait(); //wait on current child to finish before exit
		printf("[Parent, PID %d]: Child %d finished with status code %d\n",getpid(), pid, lifespan-1);
		exit(exitcode);
	}
lifespan --; //decrement life

}

exit (0);
}

