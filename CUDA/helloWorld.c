#include <stdio.h>

__global__ void cuda_hello () {
    printf ("Na GPU! \n");
}

int main () {
    printf("Na CPU principal! \n");
    cuda_hello<<<1,1>>>();
    cudaDeviceSynchronize();
    return 0;
}