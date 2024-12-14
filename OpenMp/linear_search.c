#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int parallel_linear_search(int *arr, int n, int target) {
    int found = -1;

    #pragma omp parallel for shared(found)
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            #pragma omp critical
            {
                if (found == -1) {
                    found = i;
                }
            }
        }
    }

    return found;
}

int main(int argc, char **argv) {
    char *awnser[] = { "bad", "ok" };
    int *vector;
    int i, n, target, index_seq;
    double start_s, end_s, elapsed_s;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number of elements>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]);
    n *= 10e3;

    printf("number of elements: %d * 10E3\n", (int)(n / 10e3));

    vector = (int *)malloc(n * sizeof(int));
    if (vector == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    for (i = 0; i < n; i++) {
        vector[i] = rand();
    }

    // Escolhendo um elemento-alvo
    target = vector[n / 2]; // Escolha um valor garantido no vetor para teste

    // Busca Sequencial Paralela
    start_s = omp_get_wtime();
    index_seq = parallel_linear_search(vector, n, target);
    end_s = omp_get_wtime();

    elapsed_s = end_s - start_s;

    // Validar resultado
    int is_ok = (index_seq != -1 && vector[index_seq] == target);

    printf("Search result is %s\nsearch_time: %.3f seconds\n", awnser[is_ok], elapsed_s);

    free(vector);

    return 0;
}