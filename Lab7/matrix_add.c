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

int COUNT = 0;

void readPrep(struct aiocb* block, int offset, off_t TransferLength);
void writePrep(struct aiocb* block, int offset, off_t TransferLength);
int checkBlock(struct aiocb* output, int blockSize, int tranLen, int size);
void matrix_add(struct aiocb* block, struct aiocb* new, int size, int scalar);

int main(int argc, char* argv[]) {
    int  matSize, blockNum, blockSize, bytes, scalar;
    int off1 = 0;
    int off2 = 0;
    int newLine = 0;
    struct aiocb current, next, last, new;
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

    for (off1 = bytes; off1 < ((matSize * matSize) * 4); off1 = off1 + bytes) {
        readPrep(&next, off1, bytes);
        aio_read(&next);

        newLine = checkBlock(&new, blockSize, bytes, matSize);

        matrix_add(&current, &new, matSize, scalar);
        memcpy(&last, &new, sizeof(struct aiocb));

        while (aio_error(&next) == EINPROGRESS) {
        }

        writePrep(&last, off2, bytes);
        aio_write(&last);

        off2 = off1 + bytes + newLine;
        newLine = 0;
           
        while (aio_error(&last) == EINPROGRESS) {
        }
        aio_return(&last);
        memcpy(&current, &next, sizeof(struct aiocb));
    }//end of for loop

    checkBlock(&new, blockSize, bytes, matSize);

    matrix_add(&current, &new, matSize, scalar);

    writePrep(&new, off2, bytes);
    aio_write(&new);
   
    while (aio_error(&new) == EINPROGRESS) {};
    aio_return(&new);

    //sync the final block, still only a request so check for failure to sync
    if (aio_fsync(O_SYNC, &new) == -1) {
        printf("Error: current failed to sync (line 216)\n");
    }

    printf("\nstarted at: %d - finished at: %ld\n", startT, time(NULL));
    
    return 0;
}

void readPrep(struct aiocb* block, int offset, off_t tranLen) {
    memset(block, 0, sizeof(struct aiocb));
    block->aio_fildes = STDIN_FILENO;
    block->aio_offset = offset;
    block->aio_buf = malloc(tranLen);
    block->aio_nbytes = tranLen;
}

void writePrep(struct aiocb* block, int offset, off_t tranLen) {
    block->aio_fildes = STDOUT_FILENO;
    block->aio_offset = offset;
    block->aio_nbytes = tranLen;
}

int checkBlock(struct aiocb* output, int blockSize, int tranLen, int size) {
    int i = 0;
    blockSize /= 4;

    if (((COUNT % blockSize) + blockSize) >= size) {
        readPrep(output, 0, tranLen + 1);
        i = 1;
    }
    else readPrep(output, 0, tranLen);

    return i;
}

void matrix_add(struct aiocb* block, struct aiocb* new, int size, int scalar) {
    signed int hold, extra = 0;
    char nBuffer[5], lineBuffer[2] = { '\n' };

    for (unsigned int bytes = 0; bytes < block->aio_nbytes; bytes += 4) {
        COUNT++;
        memset(nBuffer, '\0', sizeof(nBuffer));
        memmove(nBuffer, (void*)block->aio_buf + bytes, 4);
        hold = atoi(nBuffer) + scalar;
        memset(nBuffer, '\0', sizeof(nBuffer));

        sprintf(nBuffer, "%d", hold);

        memmove((void*)new->aio_buf + (bytes + extra), nBuffer, 4);

        if (COUNT % size == 0) {
            extra++;
            memmove((void*)new->aio_buf + (bytes + extra), lineBuffer, 1);
        }
    }
}
