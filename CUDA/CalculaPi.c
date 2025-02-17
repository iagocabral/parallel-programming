#include <stdio.h>
#include <cuda_runtime.h>
#define NUM_STEPS 80000
#define BLOCK_SIZE 2
__global__ void calculatePi(double *sum_dev) {
int i = blockIdx.x * blockDim.x + threadIdx.x;
double x;
double step = 1.0 / (double)NUM_STEPS;
if (i < NUM_STEPS) {
x = (i + 0.5) * step;
sum_dev[i] = 4.0 / (1.0 + x * x);
}
}
int main() {
double *sum_dev;
double pi;
double step = 1.0 / (double)NUM_STEPS;
cudaError_t cudaStatus;
// Aloca memoria para a soma
cudaStatus = cudaMalloc((void **)&sum_dev, NUM_STEPS * sizeof(double));
if (cudaStatus != cudaSuccess) {
fprintf(stderr,"cudaMalloc failed: %s\n", cudaGetErrorString(cudaStatus));
return 1;
}
// Inicia o kernel para calcular a soma
int num_blocks = (NUM_STEPS + BLOCK_SIZE - 1) / BLOCK_SIZE;
calculatePi<<<num_blocks, BLOCK_SIZE>>>(sum_dev);
cudaStatus = cudaGetLastError();
if (cudaStatus != cudaSuccess) {
fprintf(stderr,"calculatePi launch failed: %s\n", cudaGetErrorString(cudaStatus));
return 1;
}
// Copia os resultados de volta para o host
double *sum = (double *)malloc(NUM_STEPS * sizeof(double));
cudaStatus = cudaMemcpy(sum, sum_dev, NUM_STEPS * sizeof(double), cudaMemcpyDeviceToHost);
if (cudaStatus != cudaSuccess) {
fprintf(stderr,"cudaMemcpy failed: %s\n", cudaGetErrorString(cudaStatus));
return 1;
}
// Calcula o final da soma no ho
pi = 0.0;
for (int i = 0; i < NUM_STEPS; i++) {
pi += sum[i];
}
pi *= step;
printf("Pi = %f\n", pi);
free(sum);
cudaFree(sum_dev);
return 0;
}
