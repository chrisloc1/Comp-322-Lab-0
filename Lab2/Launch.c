#include <stdio.h> 
#include <stdlib.h> 
#include<fcntl.h>
#include<string.h> 
#include <unistd.h> 

int main(int argc, char* argv[]) {
	//char FileName[500] = { '\0' };
	char *newargv[] = { NULL, "hello", "world", NULL };
	char *newenviron[] = { NULL };
	pid_t pid;
	int stat;


	pid = fork();

	
	//printf("PPID: %d, PID: %d ", getppid(), getpid());

	if (pid == 0) {
		execve(argv[1], newargv, newenviron);
		exit(0);
	}
	else {
		printf("CPID: %d \n", pid);
	}

	//strcpy(FileName, argv[1]);
	newargv[0] = argv[1];

	

	waitpid(pid, &stat, 0);

	printf("RETVAL: %d \n", stat);
}