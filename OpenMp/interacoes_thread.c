#include <stdio.h>
#include <omp.h>
#include <string.h>
#define MAX 10
int main(int argc, char *argv[]) {
int vetor[omp_get_max_threads()];
memset(&vetor, 0, 4*omp_get_max_threads());
#pragma omp parallel
{
#pragma omp for
for(int i=0;i<MAX;i++) {
vetor[omp_get_thread_num()]++;
} /* fim-for */
} /*fim omp parallel */
for(int i=0;i<omp_get_max_threads(); i++)
printf("Thread[%d] iterou %d vezes \n", i, vetor[i]);
return 0;
}