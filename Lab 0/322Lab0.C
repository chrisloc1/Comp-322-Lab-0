//Christian Locker Comp 322 Lab 0
#include<stdio.h> 
#include<stdlib.h> 
#include<fcntl.h>
//#include <unistd.h>

int binToNum(char binAr[]);

int main(int argc, char* argv[]) {
	char bin8[8] = { '\0' };
	char FileName[500] = { '\0' };
	char symbol;
	//int last = 0;
	int parity = 0;
	int count = 1;
	int fd, sz;
	//FILE *inF = NULL;
	


	//printf("Welcome to binary reader! Opening file to read. \n");
	//inF = fopen("binary.txt", "r");
	printf("Welcome to binary reader! \n");
	//scanf("%s", FileName);
	//fd = open("binary.txt", O_RDONLY);

	//printf("%s \n", argv);
	//FileName = argv[1];
	strcpy(FileName, argv[1]);
	//printf("%s \n", argv[5]);

	if (FileName[0] == '0' || FileName[0] == '1' || FileName[0] == '-') {
		printf("-------- -------- -------- --------\n");
		printf("%-9s%-9s%-9s%-9s\n", "Original", "ASCII", "Decimal", "Parity");
		printf("-------- -------- -------- --------\n");/**/
		//printf("%s \n", FileName);

		if (FileName[0] == '-') count ++;
		while (argv[count]) {
			strcpy(bin8, argv[count]);
			count++;
			/*for (int i = 0; i <= 7; i++) {
				if (FileName[count] == '0' || FileName[count] == '1') bin8[i] = FileName[count];
				else bin8[i] = '0';
				count++;
			}*/
			for (int i = 1; i <= 7; i++) {
				if (bin8[i] != '1' && bin8[i] != '0') bin8[i] = '0';
			}/**/

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
			if (parity % 2 == 1) printf("%-9s \n", "ODD");
			else printf("%-9s \n", "EVEN");
			parity = 0;
			memset(bin8, 0, sizeof(bin8));
		}/**/
	}
	else {
		fd = open(argv[1], O_RDONLY);
		if (fd == NULL) {
			perror("Error");
			exit(1);
		}

		printf("File successfully read, printing table. \n \n");
		printf("-------- -------- -------- --------\n");
		printf("%-9s%-9s%-9s%-9s\n", "Original", "ASCII", "Decimal", "Parity");
		printf("-------- -------- -------- --------\n");/**/


		while (sz = read(fd, bin8, 8)) {

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
			if (parity % 2 == 1) printf("%-9s \n", "ODD");
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
	}
	//printf("%s \n", argv[1]);
	

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