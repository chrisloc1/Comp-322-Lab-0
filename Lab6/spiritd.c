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

pid_t MOLE1, MOLE2;


int main(int argc, char* argv[]) {
	int fd0, fd1, fd2;
	pid_t pid = 0;
	pid_t sid = 0;
	struct rlimit lim;

	umask(0);

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
	printf("before: %ld  %ld\n", lim.rlim_cur, lim.rlim_max);

	for (int i = 0; i <= lim.rlim_max; i++) {
		close(i);
	}

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	//getrlimit(RLIMIT_NOFILE, &lim);
	//printf("after: %ld  %ld\n", lim.rlim_cur, lim.rlim_max);

	signal(SIGTERM, handleSig);
	signal(SIGUSR1, handleSig);
	signal(SIGUSR2, handleSig);

	return 0;
}

void handleSig(int sig){
	char* newenviron[] = { NULL };
	char* newargv[] = { NULL, NULL, NULL };
	srand(time(NULL));

	if (sig == 10 || sig == 12) {
		if (sig == 10) kill(MOLE1, SIGQUIT);
		if (sig == 12) kill(MOLE2, SIGQUIT);

		if (rand() % 2 == 0) {
			MOLE1 = fork();
			newargv[1] = "mole1";
			execve("mole.c", newargv, newenviron);
		}
		if (rand() % 2 == 1) {
			MOLE2 = fork();
			newargv[1] = "mole2";
			execve("mole.c", newargv, newenviron);
		}
	}
	else if (sig == 15) {
		kill(0, SIGQUIT);
	}
}
