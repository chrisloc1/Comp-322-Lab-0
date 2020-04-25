#include<stdio.h> 
#include<stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <time.h> 

void eat();
void think();

int main(int argc, char* argv[]) {
	eat();
	think();
	//semaphore chopstick[5];
	/*do {
		wait(chopstick[i])
		//wait(chopstick[(i+1) %])
		// eat for a while
		signal(chopstick[i]);
		//signal(chopstick[(i+1)]);
	} while (true);*/
}

void eat() {
	printf("Philosopher #n is eating");
	usleep(rand());
}
void think() {
	printf("Philosopher #n is thinking");
	usleep(rand());
}
