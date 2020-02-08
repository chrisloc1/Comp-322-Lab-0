//Christian Locker Comp 322 Lab 0
#include<stdio.h> 
#include<stdlib.h> 

int binToNum(char binAr[]);

int main() {
	char bin8[8];
	FILE *inF = NULL;
	char symbol;
	int last = 0;

	printf("Welcome to binary reader! Opening file to read. \n");
	inF = fopen("binary.txt", "r");
	if (inF == NULL) {
		perror("Error");
		exit(1);
	}

	printf("File successfully read, printing table. \n \n");
	printf("-------- -------- -------- --------\n");
	//printf("%-9s%-9s%-9s%-9s%-9s\n", "Original", "ASCII", "Decimal", "Parity", "T.Error");
	printf("%-9s%-9s%-9s%-9s\n", "Original", "ASCII", "Decimal", "Parity");
	printf("-------- -------- -------- --------\n");
	
	int count = 1;
	fscanf(inF, " ");
	fgets(bin8, 9, (FILE*)inF);

	while (!feof(inF) || last == 1) {

		//printf("%d:%s\t", count, bin8);
		printf("%-9s", bin8);
		
		symbol = binToNum(bin8);
		printf("%-9c", symbol);
		printf("%-9d", symbol);

		/*if(bin8[0] == '0') printf("%-9s%-9s \n", "ODD", "TRUE");
		else if (bin8[0] == '1') printf("%-9s%-9s \n", "EVEN", "FALSE");*/
		if (bin8[0] == '0') printf("%-9s \n", "ODD");
		else if (bin8[0] == '1') printf("%-9s \n", "EVEN");

		count++;
		memset(bin8, 0, sizeof(bin8));
		if (last == 0) {
			fscanf(inF, " ");
			fgets(bin8, 9, (FILE*)inF);
			if (feof(inF)) {
				for (int i = 1; i <= 7; i++) {
					if (bin8[i] != '1' && bin8[i] != '0') bin8[i] = '0';
				}
				last = 1;
			}
		}
		else last = 0;
	}/**/


	printf("Program complete, closing the file. \n");
	int fclose(FILE *fp);

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