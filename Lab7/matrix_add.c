#include<stdio.h> 
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <aio.h>
//#include <aiocb.h>

//int COUNT = 0;

//void matrix_add(int block[], int size, int scalar);
void readPrep(struct aiocb* block, int offset, off_t TransferLength);

int main(int argc, char* argv[]) {
    int  matSize, blockNum, blockSize, bytes, scalar;
    int off1 = 0;
    int off2 = 0;
    struct aiocb current, next, last;
    int startT = time(NULL);
    srand(time(NULL));

    matSize = atoi(argv[1]);
    blockNum = atoi(argv[2]);

    if (blockNum == 0) {
        printf("Error: blocks is 0 \n");
        exit(EXIT_FAILURE);
    }

    blockSize = matSize / blockNum;
    blockSize = blockSize * 4;
    bytes = blockSize * blockSize;

    scalar = rand() % 201;
    if (scalar <= 100)
        scalar = scalar * -1;
    else if (scalar > 100)
        scalar -= 100;

    readPrep(&current, off1, bytes);

    aio_read(&current);

    while (aio_error(&current) == EINPROGRESS) {
    }
    aio_return(&current);

    /*for (off1 = bytes; off1 < ((matSize * matSize) * 4); off1 = off1 + bytes) {
        readPrep(&next, off1, bytes);
        aio_read(&next);
    }*/
    return 0;
}

void readPrep(struct aiocb* block, int offset, off_t tranLen) {
    memset(block, 0, sizeof(struct aiocb));
    block->aio_fildes = STDIN_FILENO;
    block->aio_offset = offset;
    block->aio_buf = malloc(tranLen);
    block->aio_nbytes = tranLen;
}


/*matrix_add(int block[], int size, int scalar) {
    //    for i = 1 ..size
    //        for j = 1 ..size
    //           block[i][j] += scalar;
    //end for
    //    end for
}*/
