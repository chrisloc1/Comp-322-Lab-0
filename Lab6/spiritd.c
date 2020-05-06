#include<stdio.h> 
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char* argv[]) {
	pid_t pid;
	struct rlimit lim;
	int fcopy;

	umask(0);

	pid = fork();
	if (pid > 0) {
		return 0;
	}

	setsid();
	chdir("/");
	getrlimit(RLIMIT_NOFILE, &lim);
	printf("before: %ld  %ld\n", lim.rlim_cur, lim.rlim_max);

	for (int i = 0; i < lim.rlim_cur; i++) {
		fcopy = dup(i);
		close(i);
		//fcopy = open()
	}

	getrlimit(RLIMIT_NOFILE, &lim);
	printf("after: %ld  %ld\n", lim.rlim_cur, lim.rlim_max);



	return 0;
}
