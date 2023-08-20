#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char  *argv[]) {

FILE *seed = fopen(argv[1], "r");//Reads the seed file.
char fileString[255]; //create string space for seed file read, dummy number
fgets(fileString, 255, seed); //get the first line,store it in fileString 

int seedNum = atoi(fileString); //change the string in the file to be an int
printf("Seed value: %d\n", seedNum);  //print the seed number
srand(seedNum); //seeds the random number generator
char cwd[255]; //char holder
for (int i=0; i<5; i++) { //visit 5 directories
	int dirNum =(rand()) %6; //rand num to use to get which directory to visit
//now go to corresponding location
	if (dirNum == 0) { //home
	chdir("/home");
	}
	else if (dirNum == 1) { //proc
	chdir("/proc"); 
	}
	
	else if (dirNum ==2) { //proc/sys
	chdir("/proc/sys");
	}
	
	else if (dirNum == 3) { //usr
	chdir("/usr");
	}
	
	else if (dirNum == 4) { //boot
	chdir("/boot");
	}
                
	else if (dirNum == 5) { //sbin
	chdir("/sbin");
	}
	
	getcwd(cwd,sizeof(cwd));
	printf("Selection #%d: %s\n", i+1, cwd); //print directory
	
	//create child
	int pid = fork(); 
	if (pid < 0) { //fork failed,
		fprintf(stderr, "fork failed\n");
	}
	
	if (pid == 0) { //child	
		sleep(1); //wait for parent statement
		printf("[Child, PID: %d]: Executing 'ls -tr' command..\n", getpid());  //print statement for child
		
		char *cmd = "ls"; //create char to input into execvp
		char *argv[3] = {"ls", "-tr", NULL}; 
		execvp(cmd, argv); //use execvp to ls -tr 
		exit(0); //exit child
	}
	else { //parent
		printf("[Parent]: I am waiting for PID %d to finish\n",pid);
		wait();//wait on current child to finish before exit
		printf("[Parent]: Child %d finished with status code %d\n", pid,0); 
	}

	
   

}


//exit the while loop, 5 directories have been visited

exit (0);
}

