#include<stdio.h> 
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int fd0, fd1, fd2;
	pid_t pid = 0;
	pid_t sid = 0;
	struct rlimit lim;

	umask(0);

	pid = fork();
	if (pid < 0)
	{
		printf("fork issue\n");
		exit(1);
	}
	else if(pid > 0) {
		printf("cpid %d\n", pid);
		exit(0);
	}

	sid = setsid();
	if (sid < 0) exit(1);

	chdir("/");
	getrlimit(RLIMIT_NOFILE, &lim);
	printf("before: %ld  %ld\n", lim.rlim_cur, lim.rlim_max);

	for (int i = 0; i <= lim.rlim_max; i++) {
		//fcopy = dup(i);
		close(i);
		//fcopy = open()
	}

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	getrlimit(RLIMIT_NOFILE, &lim);
	printf("after: %ld  %ld\n", lim.rlim_cur, lim.rlim_max);

	return 0;
}
