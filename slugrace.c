#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>



int main(int argc, char  *argv[]) {
struct timespec start, end, totalend;
int slugnum = 0; //count number for slug
int slugpids[4] = {0,0,0,0}; //create array to keep track of the pids for each slug
int activechild =4; //keep track of active kids
int status[4] = {0,0,0,0}; //hold status of each slug to see if completed

//create 4 children (slugs) to race
clock_gettime(CLOCK_MONOTONIC, &start); //start the clock before
while (slugnum < 4) { 
	
	pid_t pid = fork();
   	slugpids[slugnum] = pid; //get pid for each child
    	
    
	if (slugpids[slugnum] < 0) { //fork failed,
		fprintf(stderr, "fork failed\n");
	}
	if (pid == 0) { //child
		 //child process, increment the active children
		char *cmd = "./slug"; //create char to input into execvp
		char *para ="0"; //default char for input in execvp
		if (slugnum ==0) {
			para = "1"; }
		if (slugnum ==1) {
			para = "2"; }
		if (slugnum ==2) {
			para = "3"; }
		if (slugnum ==3) {
			para = "4"; }
		
		char *argv[3] = {"./slug", para ,NULL}; //create array to put into execvp
		printf("[Child, PID: %d]: Executing '%s %s' command\n",getpid() ,argv[0], argv[1]);  //print that the child will begin ./slug  
		
		execvp("./slug",argv); //each child run slug
	}
	else { //parent
	printf("[Parent] I forked off child %d. \n", getpid());
	
	}
	
slugnum++; //increase counter since another child has been created	 
}while (activechild > 0) { //loop continues until every child is done
	int counter = 0; 
	while (counter < 4) { //counter to run through 4 times
	status[counter] = waitpid(slugpids[counter],0,WNOHANG); //waitpid returns the status of each pid, store in the array
	
	
	if (status[counter] == slugpids[counter]) { //if the waitpid returns the pid of the child, child complete
	//COMPLETE 
	clock_gettime(CLOCK_MONOTONIC, &end); //endtimer
	double time = end.tv_sec - start.tv_sec; //calculate time for this child
	printf("Child %d finished! Elapsed time: %f \n",slugpids[counter],time ); //print out the seconds taken
	
	 }
	 
	 counter++; //increment counter
	 } 
	 
usleep(200000); //wait .2 seconds to recheck status of children

printf("The race is still going, the following children are still racing: "); //print that the race is still going since there is still active children
	

if (activechild >0) { //if its still running print
for (int i=0; i<4; i++) {
	if (status[i] == 0) { //if 0, still running and hasnt been changed yet
	printf("%d,", slugpids[i]);
	}
}
printf("\n");
 if ( status[0] !=0 && status[1] !=0 && status[2] !=0 && status[3] !=0) {
	activechild =0; //breaks out of while loop, race is done
	}
}
  
 
}

clock_gettime(CLOCK_MONOTONIC, &totalend); //end the full timer
double totaltime = totalend.tv_sec - start.tv_sec; //calculate the time taken
printf("The race is complete, total elapsed time: %f \n",totaltime);
return 0;
}
