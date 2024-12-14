#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

void merge(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void parallel_merge_sort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallel_merge_sort(arr, l, m);

            #pragma omp section
            parallel_merge_sort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char **argv) {
    char *awnser[] = { "bad", "ok" };
    int *vector, *test;
    int i, n, is_ok;
    double elapsed_q, start_q, end_q;
    double elapsed_p, start_p, end_p;

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

    test = (int *)malloc(n * sizeof(int));
    if (test == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    for (i = 0; i < n; i++) {
        vector[i] = rand();
        test[i] = vector[i];
    }

    // Teste com qsort (sequencial)
    start_q = omp_get_wtime();
    qsort(test, n, sizeof(int), compare);
    end_q = omp_get_wtime();
    elapsed_q = end_q - start_q;

    // Teste com Merge Sort Paralelo
    start_p = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        parallel_merge_sort(vector, 0, n - 1);
    }
    end_p = omp_get_wtime();
    elapsed_p = end_p - start_p;

    // Comparar os resultados
    is_ok = (memcmp(vector, test, n * sizeof(int)) == 0);

    printf("sorted values are %s\nqsort_time: %.3f seconds\nmerge_sort_time: %.3f seconds\n",
           awnser[is_ok], elapsed_q, elapsed_p);

    free(vector);
    free(test);

    return 0;
}