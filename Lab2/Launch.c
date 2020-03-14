#include <stdio.h> 
#include <stdlib.h> 
#include<fcntl.h>
#include<string.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h> 

void ProcessPID(pid_t pid, char* FileName[]);

int main(int argc, char* argv[]) {
	
	pid_t pid;
	int stat;

	pid = fork();
	
	ProcessPID(pid, argv);

	

	waitpid(pid, &stat, 0);

	printf("RETVAL: %d \n", stat);
}

void ProcessPID(pid_t pid, char* FileName[]) {
	char *newargv[] = { NULL, FileName[1], NULL };
	char *newenviron[] = { NULL };

	//newargv[0] = argv[1];

	if (pid == 0) {
		execve(FileName[1], newargv, newenviron);
		exit(0);
	}
	else {
		printf("CPID: %d \n", pid);
		//printf("CPID: %d %s\n", pid, argv[2]);
	}
}