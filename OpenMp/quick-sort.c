#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void parallel_quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        #pragma omp parallel sections
        {
            #pragma omp section
            parallel_quick_sort(arr, low, pi - 1);

            #pragma omp section
            parallel_quick_sort(arr, pi + 1, high);
        }
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

    // Teste com Quick Sort Paralelo
    start_p = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        parallel_quick_sort(vector, 0, n - 1);
    }
    end_p = omp_get_wtime();
    elapsed_p = end_p - start_p;

    // Comparar os resultados
    is_ok = (memcmp(vector, test, n * sizeof(int)) == 0);

    printf("sorted values are %s\nqsort_time: %.3f seconds\nquick_sort_time: %.3f seconds\n",
           awnser[is_ok], elapsed_q, elapsed_p);

    free(vector);
    free(test);

    return 0;
}