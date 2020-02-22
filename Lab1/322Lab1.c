#include<stdio.h> 
#include<stdlib.h> 

/*
The program prints the number of seconds since.. 		(see time(2))
The program creates a child process 			(see fork(2))
The program will wait for the child to finish			(see waitpid(2))
The program and its child reports on the information
The process ID of its parent  			(see getppid(2))
Its own process ID					(see getpid(2))
The process ID of its child (if applicable)		(see fork(2))
The return status of its child (if applicable)		(see exit(3), waitpid(2))
The program will report the following time information	(see times(2))
user time
 system time
 user time of child
 system time of child
The program prints the number of seconds since..	(see time(2))
*/

int main() {

	/*printf("Start: %d", 1);
	printf("PPID: %d, PID: %d", 1, 2);
	printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %d", 1, 2, 3, 4);
	printf("User: %d, SYS: %d", 1, 2);
	printf("CUSER: %d, CSYS: %d", 1, 2);
	printf("STOP: %d", 1);*/

	system("pause");
}