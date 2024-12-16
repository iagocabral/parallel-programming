#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void add(int N, float *a, float *b, float *c) {
    int tid=0;
    while (tid<N) {
        c[tid]=a[tid]+b[tid];
        tid++;
    }
}

int main(int argc, char *argv[]) {
    struct timeval begin, end;
    float *a, *b, *c;
    if (argc != 2) {
        exit(1);
    }
    int N = atoi(argv[1]);
    a = (float *)malloc(N * sizeof(float));
    b = (float *)malloc(N * sizeof(float));
    c = (float *)malloc(N * sizeof(float));
    for (int i = 0; i < N; i++) {
        a[i] = -i;
        b[i] = i * i;
    }
    gettimeofday(&begin, NULL);
    add(N, a, b, c);
    gettimeofday(&end, NULL);
    double cpuTime = 1000000*(double)(end.tv_sec - begin.tv_sec);
    cpuTime += (double)(end.tv_usec - begin.tv_usec);
    
    for(int i = 0; i < N; i++) {
        printf("%6.0f + %6.0f = %f6.0\n", a[i], b[i], c[i]);
    }
    printf("Tempo de execução da CPU: %9.2f\n", cpuTime);

    free(a);
    free(b);
    free(c);
    return 0;
}

struct timeval begin, end;
float *a, *b, *c;
if (argc ! = 2)
exit (1) ;
int N = atoi(argv[1]) ;
a = (float *) malloc(N*sizeof(float));

b = (float *) malloc(N*sizeof(float));

c = (float *) malloc(N*sizeof(float));

for (int i=0; i<N; i++) {

a [i] = -i; b[il = i*i;

} /*fim-for */