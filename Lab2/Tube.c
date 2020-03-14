#include <stdio.h> 
#include <stdlib.h> 
#include<fcntl.h>
#include<string.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h> 

void ProcessPID(pid_t cpid1, pid_t cpid2, char* FileName[], int fd[2]);

int main(int argc, char* argv[]) {
	pid_t pid1, pid2;
	int stat1, stat2, pipefd[2];

	pipe(pipefd);

	pid1 = fork();
	pid2 = fork();

	ProcessPID(pid1, pid2, argv, pipefd);

	/*else{
		printf("CPID1: %d CPID2: %d \n", pid1, pid2);
	}*/

	waitpid(pid1, &stat1, 0);
	waitpid(pid2, &stat2, 0);
	
	if (pid1 > 0 && pid2 > 0)
		printf("RETVAL1: %d \nRETVAL2: %d \n", stat1, stat2);
}

void ProcessPID(pid_t cpid1, pid_t cpid2, char* FileName[], int fd[2]) {
	char* newargv1[] = { NULL, FileName[1], NULL };
	char* newargv2[] = { NULL, FileName[2], NULL };
	char* newenviron[] = { NULL };

	if (cpid1 > 0 && cpid2 > 0) {
		printf("CPID1: %d \nCPID2: %d \n", cpid1, cpid2);
		close(fd[0]);
		close(fd[1]);
	}
	if (cpid1 == 0 && cpid2 != 0) {
		dup2(fd[0], 0);
		execve(FileName[1], newargv1, newenviron);
		exit(0);
	}
	else if(cpid2 == 0 && cpid1 != 0) {
		dup2(fd[0], 0);
		execve(FileName[2], newargv2, newenviron);
		exit(0);
	}
}