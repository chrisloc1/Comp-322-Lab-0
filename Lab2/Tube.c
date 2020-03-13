#include <stdio.h> 
#include <stdlib.h> 
#include<fcntl.h>
#include<string.h> 
#include <unistd.h> 

int main() {
	pid_t pid1, pid2;


	pid1 = fork();
	pid2 = fork();

	if (pid1 == 0) {
		exit(0);
	}
	if (pid2 == 0){
		exit(0);
	}
	else {
		printf("CPID1: %d CPID2: %d \n", pid1, pid2);
	}

}