#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <sys/times.h>
#include <sys/wait.h> 
#include <unistd.h> 
#include <sys/types.h> 

void reportInfo(pid_t passP, int ret);

int main() {
	pid_t pid;
	int stat;
	struct tms buf;
	clock_t sinceboot;

	printf("Start: %ld \n", time(NULL));

	pid = fork();
	//wait(&stat);
	//waitpid(pid, &stat, 0);

	reportInfo(pid, stat);

	sinceboot = times(&buf);

	printf("\n User: %jd, SYS: %jd \n", buf.tms_utime, buf.tms_stime);
	printf("CUSER: %jd, CSYS: %jd \n", buf.tms_cutime, buf.tms_cstime);
	printf("STOP: %ld \n", time(NULL));
	
}

void reportInfo(pid_t passP, int ret) {
	int stat;
	

	printf("PPID: %d, PID: %d ", getppid(), getpid());
	waitpid(passP, &ret, 0);

	if (passP != 0) {
		//waitpid(passP, &ret, 0);
		printf("CPID: %d, RETVAL: %d ", passP, ret);
		exit(0);
	}
}