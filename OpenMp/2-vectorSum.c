#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long long int sum(int *v, long long int N){
	long long int i = 0, sum = 0;
	#pragma omp parallel for reduction(+:sum)
	for(i = 0; i < N; i++)
		sum += v[i];
	
	return sum;
}

int main(int argc, char **argv){
	char *awnser[] = { "bad", "ok" };
	
	long long int i, sumv, n;
	double start, end, elapsed;
	
	if(argc < 2){
		fprintf(stderr, "Usage: %s <number of elements>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atoll(argv[1]);
	n *= 10e6;
	
	printf("number of elements: %lld x 10E6\n", (long long int) (n / 10e6));
	
	int *vector = (int *) calloc(n, sizeof(int));
	if(vector == NULL){
		fprintf(stderr, "Out of memory!\n");
		exit(EXIT_FAILURE);
	}
	#pragma omp parallel for
	for(i = 0; i < n; i++)
		vector[i] = 1;
	
	start = omp_get_wtime();
	sumv = sum(vector, n);
	end = omp_get_wtime();
	
	elapsed = end - start;
	
	printf("sum value is %s\ntime: %.3f seconds\n", awnser[sumv == n], elapsed);

	free(vector);
	
	return 0;
}