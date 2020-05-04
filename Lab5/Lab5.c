#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]) {
	int pNum, offSet;
	unsigned int adress;
	adress = (unsigned int)atoi(argv[1]);

	/*if (argc != 2) {

	}*/

	printf("Adress %d contains: \n", adress);

	//mask the page number
	pNum = (adress & 0xFFFFF000) >> 12;
	offSet = adress & 0x00000FFF;

	printf("page #: %d \n", pNum);
	printf("offset: %d \n", offSet);

	return 0;
}