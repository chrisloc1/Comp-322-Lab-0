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

bool CONT = true;

void eat(int pNum);
void think(int pNum);
void handleSig(int sig);

int main(int argc, char* argv[]) {
	int phil[] = { 0, 1, 2, 3, 4 };
	int CycleCount = 0;

	srand(time(NULL));
	signal(SIGTERM, handleSig);

	eat(phil[0]);
	think(phil[1]);

	//pid_t groupPID = getpid();
	//Semaphore chopstick[5] = {1,1,1,1,1};
	sem_t* chopstick[5];

	do {
		wait(chopstick[phil[0]]);
		wait(chopstick[(phil[0] + 1) % 5]);
		// eat for a while
		signal(chopstick[phil[0]]);
		signal(chopstick[(phil[0] +1)%5]);

		CycleCount++;
	} while (cont);/**/

	//SETPGID(getpid(), groupPID);

	//sem_close(chopstick[0]);
	//sem_unlink(chopstick[0]);
	//sem_destroy(chopstick[0]);

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
