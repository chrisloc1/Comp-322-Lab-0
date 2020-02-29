#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <sys/times.h>
#include <sys/wait.h> 
#include <unistd.h> 
#include <sys/types.h> 




// Executable Name: time-4-baby-and-me
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
	
	clock_t times(struct tms *buffer);

	int ID, stat;
	pid_t pid, cpid;

	printf("Start: %ld \n", time(NULL));

	if ((ID = fork()) == 0) exit(0);
	else cpid = waitpid(pid, &stat, 0);


	printf("PPID: %d, PID: %d \n", getppid(), getpid());
	printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %d \n", getppid(), getpid(), ID, cpid);
	//printf("User: %jd, SYS: %jd \n", times(&tms_utime), times(&tms_stime));
	//printf("CUSER: %jd, CSYS: %jd \n", times(&tms_cutime), times(&tms_cstime));/**/

	printf("STOP: %ld \n", time(NULL));

	//system("pause");
}