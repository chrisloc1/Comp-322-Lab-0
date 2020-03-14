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
	pid_t pid;
	int stat;


	pid = fork();

	

	if (pid == 0) {
		execve(argv[1], newargv, newenviron);
		exit(0);
	}
	else {
		printf("CPID: %d \n", pid);
		//printf("CPID: %d %s\n", pid, argv[2]);
	}

	newargv[0] = argv[1];

	

	waitpid(pid, &stat, 0);

	printf("RETVAL: %d \n", stat);
}