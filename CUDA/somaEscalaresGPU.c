#include <stdio.h>
#include <stdlib.h>

global_ void add(int a, int b, int *c) {
    *c = a + b;
    printf ("Na GPU!\n");
} /* fim-global */


int main (int argc, char *argv[]){
    int c;
    int *dev_c;

    int a = atoi(argv [1]);
    int b = atoi(argv [2]);
    cudaMalloc( (void**)&dev_c, sizeof (int));
    add<<<1,1>>>(a, b, dev_c);
    cudaMemcpy (&c, dev_c, sizeof(int), cudaMemcpyDeviceToHost);
    printf("%d + %d = %d\n", a, b, c);
    CudaFree (dev_c);
    return 0;
}
/* fim-main */