#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char  *argv[]) {

int val = atoi(argv[1]); //read command line arg and change to int
//use this value to determine which files to open
char* file; //variable to be used for seeding file
if (val == 1) { //open seed slug 1.txt,
	file = "seed_slug_1.txt";
	}
	
else if (val ==2) { //seed slug 2.txt
	file = "seed_slug_2.txt";
	}
	
else if (val == 3) { //textttseed slug 3.txt
	file = "textttseed_slug_3.txt";
	}
	
else if (val == 4) { //seed slug 4.txt
	file = "seed_slug_4.txt";
	}
else {
	fprintf(stderr, "invalid input\n"); //invalid input, produce error
}
 
 
FILE *seed = fopen(file, "r");//Reads the seed file.
char fileString[255]; //create string space for seed file read, dummy number
fgets(fileString, 255, seed); //get the first line,store it in fileString 
int seedNum = atoi(fileString); //change the string in the file to be an int
printf("[Slug PID: %d] Executing the './slug %d command\n", getpid(), val);  //print the seed number.
srand(seedNum); //seeds the random number generator
printf("Seed value: %d\n", seedNum);  //print the seed number


//create two random numbers
int seconds =(rand()%5 +4); //random number for wait time
int coinflip = rand()%2; //num between one and two for coin flip
//print out both variables


printf("[Slug PID: %d] Delay time is %d seconds. Coin flip: %d\n", getpid(), seconds, coinflip); 

printf("[Slug PID: %d] I'll get the job done. Eventually...\n", getpid()); 

//wait 

sleep(seconds);

//coin flip decision
if (coinflip == 0) { //last -i -x
	char *cmd = "last"; //create char to input into execvp
	char *argv[4] = {"last", "-i","-x"  ,NULL}; 
	execvp(cmd, argv); //use execvpfor last -i -x
}

else { //id --group 
	char *cmd = "id"; //create char to input into execvp
	char *argv[3] = {"id", "--group" ,NULL}; 
	execvp(cmd, argv); //use execvpfor id --group

}

exit (0);
}
