#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

__globa__ void add(int N, float *a, float *b, float *c) {
    int tid=threadIdx.x;
    if (tid < N)
        c[tid]=a[tid]+b[tid];
} /* fim-add */

int main (int argc, char *argv[]){
    struct timeval begin, end;
    float *a, *b, *c; 
    if (argc != 2){
        fprintf(stderr, "Sintaxe: %s <tam_vet>\n", argv [0]);
        exit (1);
    }
    int N = atoi(argv [1]) ;
    a = (float *) malloc (N*sizeof (float));
    b = (float *) malloc (N*sizeof (float));
    c = (float *) malloc(N*sizeof (float));
    for (int i=0; i<N; i++) {
        a[i] = -i; 
        b[i] = i*i;
    }
    float *dev_a, *dev_b, *dev_c;
    cudaMalloc( (void**)&dev_a, N*sizeof(float));
    cudaMalloc( (void**)&dev_b, N*sizeof(float));
    cudaMalloc( (void**)&dev_c, N*sizeof(float));

    gettimeofday(&begin, NULL);

    cudaMemcpy(dev_a, a, N*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, N*sizeof(float), cudaMemcpyHostToDevice);
    add<<<1,N>>>(N, dev_a, dev_b, dev_c);
    cudaMemcpy(c, dev_c, N*sizeof(float), cudaMemcpyDeviceToHost);

    gettimeofday(&end, NULL);
    double gpuTime = 1000000*(double)(end.tv_sec - begin.tv_sec);
    gpuTime += (double)(end.tv_usec - begin.tv_usec);
    printf("Tempo de execução da GPU: %9.2f\n", gpuTime);
    free(a); free(b); free(c);
    cudaFree(dev_a); cudaFree(dev_b); cudaFree(dev_c);
    return 0;
}