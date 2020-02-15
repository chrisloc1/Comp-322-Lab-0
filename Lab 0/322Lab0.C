//Christian Locker Comp 322 Lab 0
#include<stdio.h> 
#include<stdlib.h> 
#include<fcntl.h>
//#include <unistd.h>

int binToNum(char binAr[]);

int main() {
	char bin8[8] = { '\0' };
	char FileName[40];
	char symbol;
	char *c = (char *)calloc(100, sizeof(char));
	//int last = 0;
	int parity = 0;
	int fd, sz;
	//FILE *inF = NULL;
	


	//printf("Welcome to binary reader! Opening file to read. \n");
	//inF = fopen("binary.txt", "r");
	printf("Welcome to binary reader! Please enter name of file to read. \n");
	//scanf("%s", FileName);
	fd = open("binary.txt", O_RDONLY);
	//fd = open(0, O_RDONLY);
	if (fd == NULL) {
		perror("Error");
		exit(1);
	}

	printf("File successfully read, printing table. \n \n");
	printf("-------- -------- -------- --------\n");
	printf("%-9s%-9s%-9s%-9s\n", "Original", "ASCII", "Decimal", "Parity");
	printf("-------- -------- -------- --------\n");/**/
	
	//printf("%-9s \n", bin8);
	//for (int i = 0; i < 8; i++) {
	//	bin8[i] = '0';
	//}
	
	//printf("%-9s \n", bin8);

	//int count = 1;
	//fscanf(inF, " ");
	//fgets(bin8, 9, (FILE*)inF);
	//sz = read(fd, bin8, 8);
	/*for (int i = 0; i < 8; i++) {
		printf("%c", bin8[i]);
	}*/
	

	while ((sz = read(fd, bin8, 8)) > 0) {

		for (int i = 1; i <= 7; i++) {
			if (bin8[i] != '1' && bin8[i] != '0') bin8[i] = '0';
		}

		//printf("%d:%s\t", count, bin8);
		//printf("%-9s", bin8);
		for (int i = 0; i <= 7; i++) {
			printf("%c", bin8[i]);
		}
		printf("\t");

		symbol = binToNum(bin8);
		printf("%-9c", symbol);
		printf("%-9d", symbol);

		for (int i = 0; i <= 7; i++) {
			if (bin8[i] == '1') parity++;
		}
		if (parity %2 == 1) printf("%-9s \n", "ODD");
		else printf("%-9s \n", "EVEN");
		parity = 0;
		//if (bin8[0] == '0') printf("%-9s \n", "ODD");
		//else if (bin8[0] == '1') printf("%-9s \n", "EVEN");

		//count++;
		read(fd, bin8, 1);
		memset(bin8, 0, sizeof(bin8));
		/*if (last == 0) {
			fscanf(inF, " ");
			fgets(bin8, 9, (FILE*)inF);
			if (feof(inF)) {
				for (int i = 1; i <= 7; i++) {
					if (bin8[i] != '1' && bin8[i] != '0') bin8[i] = '0';
				}
				last = 1;
			}
		}
		else last = 0;*/
	}/**/

	//printf("TEST TEST TST");
	printf("Program complete, closing the file. \n");
	close(fd);

	

	system("pause");
}

int binToNum(char binAr[]) {
	int dec_value = 0;
	int base = 1;
	int val = 0;

	for(int i = 7; i >= 1; i--) {
		if (binAr[i] == '0') val = 0;
		else val = 1;
		
		dec_value += val * base;
		//printf("%d ", dec_value);
		base = base * 2;
	}

	return dec_value;
}