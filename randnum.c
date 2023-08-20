#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char  *argv[]) {

int childNum= (rand()%6 +5); //Create a random number for number of child
int arrRandNum[childNum]; //creates an array with the number of children
printf("Number of children: %d\n", childNum);

for (int i=0; i<childNum; i++) { //go through number of children
	int randNum = rand(); //create random num
	arrRandNum[i] = randNum; //put rand num into array position
	}

int counter=0;
while (counter < childNum) { //go through one iteration per child
	counter++; //about to create child, add to counter
	int pid = fork();  //fork the num of children, go into loop if child
	if (pid < 0) { //fork failed,
		fprintf(stderr, "fork failed\n");
	}
	int myRand = arrRandNum[counter]; 

exit (0);
}
