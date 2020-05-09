#include<stdio.h> 
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <signal.h>

void handleSig(int sig);

pid_t MOLE1 = -1, MOLE2 = -1;
int VAL = 0;
char cwd[100];

int main(int argc, char* argv[]) {
	int fd0, fd1, fd2;
	pid_t pid = 0;
	pid_t sid = 0;
	struct rlimit lim;

	umask(0);


	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current working dir: %s\n", cwd);
	}
	else {
		perror("getcwd() error");
		return 1;
	}/**/

	pid = fork();
	if (pid < 0){
		printf("fork issue\n");
		exit(1);
	}
	else if(pid > 0) {
		printf("cpid %d\n", pid);
		exit(0);
	}

	//printf("%d\n", getppid());

	sid = setsid();
	if (sid < 0) exit(1);

	chdir("/");

	getrlimit(RLIMIT_NOFILE, &lim);

	if (lim.rlim_max == RLIM_INFINITY)
		lim.rlim_max = 1024;
	for (int i = 0; i < lim.rlim_max; i++)
		close(i);

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	signal(SIGTERM, handleSig);
	signal(SIGUSR1, handleSig);
	signal(SIGUSR2, handleSig);

	while (VAL != 1) {
		pause();
	}/**/

	/*chdir(cwd);
	//char* newargv[] = { "/mnt/c/users/chris/source/repos/322Lab6/322Lab6/mole.o", NULL, NULL };
	char* newargv[] = { "mole.o", NULL, NULL };
	newargv[1] = "mole1";
	execv(newargv[0], newargv);*/

	return 0;
}

void handleSig(int sig){
	char* newargv[] = { "mole.o", NULL, NULL};
	//char* newargv[] = { strcat(cwd, "/mole.o"), NULL, NULL };
	pid_t pid;
	srand(time(NULL));

	if (sig == 10 || sig == 12) {
		printf("USR1 signal recieved \n");
		if (sig == 10 && MOLE1 == 0) kill(MOLE1, SIGQUIT);
		else if (sig == 12 && MOLE2 == 0) kill(MOLE2, SIGQUIT);
		if (rand() % 2 == 0) {
			printf("test1 \n");
			pid = MOLE1 = fork();
			if (pid == 0) {
				chdir(cwd);
				newargv[1] = "mole1";
				execv(newargv[0], newargv);
			}
		}
		else{
			printf("test2 \n");
			pid = MOLE2 = fork();
			if (pid == 0) {
				chdir(cwd);
				newargv[1] = "mole2";
				execv(newargv[0], newargv);
			}
		}
	}
	else if (sig == 15) {
		printf("Term signal recieved, terminating \n");
		kill(0, SIGQUIT);
		VAL = 1;
	}
}
