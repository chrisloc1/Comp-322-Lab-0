#include <stdio.h> 
#include <stdlib.h> 
#include<fcntl.h>
#include<string.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h> 

int main(int argc, char* argv[]) {
	char *newargv[] = { NULL };
	char *newenviron[] = { NULL };
	pid_t pid1, pid2;
	int stat1, stat2, pipefd[2];

	pipe(pipefd);

	pid1 = fork();
	pid2 = fork();
	if (pid1 != 0 && pid2 != 0) {
		printf("CPID1: %d \nCPID2: %d \n", pid1, pid2);
		close(pipefd[2]);
	}
	if (pid1 == 0 && pid2 != 0) {
		dup2(pipefd[2], 1);
		execve(argv[1], newargv, newenviron);
		exit(0);
	}
	else if(pid2 == 0 && pid1 != 0) {
		dup2(pipefd[2], 1);
		execve(argv[2], newargv, newenviron);
		exit(0);
	}
	/*else{
		printf("CPID1: %d CPID2: %d \n", pid1, pid2);
	}*/

	waitpid(pid1, &stat1, 0);
	waitpid(pid2, &stat2, 0);
	
	if (pid1 != 0 && pid2 != 0)
		printf("RETVAL1: %d \nRETVAL2: %d \n", stat1, stat2);
}