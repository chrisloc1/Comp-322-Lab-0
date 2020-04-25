#include<stdio.h> 
#include<stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h> 

#define SEM_FILE1  "/chopstick_1A"
#define SEM_FILE2  "/chopstick_2"


bool CONT = true;

void eat(int pNum);
void think(int pNum);
void handleSig(int sig);

int main(int argc, char* argv[]) {
	int phil[] = { 0, 1, 2, 3, 4 };
	int philNum = 0;
	int CycleCount = 0;
	//Semaphore chopstick[5];
	sem_t* chopstick[5];
	sem_t* returnVal = sem_open(SEM_FILE1, O_CREAT | O_EXCL, 0666, 1);
	if (returnVal == SEM_FAILED) {
		perror(NULL);
		returnVal = sem_open(SEM_FILE1, 0);
	}/**/

	srand(time(NULL));
	signal(SIGTERM, handleSig);

	//eat(phil[0]);
	//think(phil[1]);

	pid_t groupPID = getpid();
	pid_t main = getppid();

	for (int i = 0; i < 4; i++) {
		if(getppid == main) fork();
		if (getpid() != groupPID) philNum == phil[i];
		setpgrp();
	}
	
	
	chopstick[0] = returnVal;


	do {
		sem_wait(chopstick[philNum]);
		eat(philNum);
		sem_wait(chopstick[(philNum + 1) % 5]);
		eat((philNum+1)%5);
		// eat for a while
		sem_post(chopstick[philNum]);
		think(philNum);
		sem_post(chopstick[((philNum +1)%5)]);
		think((philNum + 1) % 5);
		// think for a while

		CycleCount++;
	} while (CONT);/**/

	

	sem_close(chopstick[0]);
	sem_unlink(SEM_FILE1);
	sem_destroy(chopstick[0]);

	printf("Philosopher #%d completed %d cycles\n", phil[0], CycleCount);
	return 0;
}

void eat(int pNum) {
	printf("Philosopher #%d is eating \n", pNum);
	//printf("%d \n", rand()%10000000);
	usleep(rand()%5000000);
}
void think(int pNum) {
	printf("Philosopher #%d is thinking \n", pNum);
	usleep(rand()%5000000);
}

void handleSig(int sig){
	CONT = false;
}
