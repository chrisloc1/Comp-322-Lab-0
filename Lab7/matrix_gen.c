#include<stdio.h> 
#include<stdlib.h>
#include <time.h>

void MatrixGen(int size);

int main(int argc, char* argv[]) {
    int MSize = atoi(argv[1]);

    MatrixGen(MSize);

    return 0;
}

/**/
void MatrixGen(int size) {
    int rNum;
    srand(time(NULL));

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            rNum = rand() % 201;
            if (rNum <= 100)
                rNum = rNum * -1;
            else if (rNum > 100)
                rNum -= 100;

            printf("%d ", rNum);
        }
        printf("\n");
    }
}
/**/
