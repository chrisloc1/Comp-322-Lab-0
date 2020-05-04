#include<stdio.h> 
#include<stdlib.h>

int main(int argc, char* argv[]) {
	FILE* logfile = fopen("lab6.log", "w");
	fprintf(logfile, "Pop %s \n", argv[0]);
	fclose(logfile);
}