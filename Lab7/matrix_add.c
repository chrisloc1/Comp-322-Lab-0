#include<stdio.h> 
#include<stdlib.h>
#include <time.h>

matrix_add(int block[], int size, int scalar);

int main(int argc, char* argv[]) {

    /*size, blocks

        start_time = get current time;
    scalar = random number;
    block_size = size / blocks;
    
    for x = 1 .. blocks
        for y = 1 .. blocks
            async read request matrix[x, y]
            block = async read return matrix[x, y]
            matrix_add(block, block_size, scaler)
            async write request block
            async write return block
    end for
        end for

    end_time = get the current time
    emit end_time - start_time

    */


}

matrix_add(int block[], int size, int scalar) {
    //    for i = 1 ..size
    //        for j = 1 ..size
    //           block[i][j] += scalar;
    //end for
    //    end for
}