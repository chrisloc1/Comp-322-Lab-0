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
    int randomVar;
    srand(time(NULL));

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            randomVar = rand() % 201;
            if (randomVar <= 100)
                randomVar = randomVar * -1;
            else if (randomVar > 100)
                randomVar -= 100;

            printf("%d ", randomVar);
        }
        printf("\n");
    }
}
/**/
