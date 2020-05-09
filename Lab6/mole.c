#include<stdio.h> 
#include<stdlib.h>

int main(int argc, char* argv[]) {
	//FILE* logfile = fopen("/mnt/c/users/chris/source/repos/322Lab6/322Lab6/lab6.log", "a");
	FILE* logfile = fopen("./lab6.log", "a");
	if (logfile == NULL) {
		perror("Failed: did not read");
	}
	fprintf(logfile, "Pop %s \n", argv[1]);
	printf("mole success, closing \n");
	fclose(logfile);
	return 0;
}
