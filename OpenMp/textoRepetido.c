#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define MAX 1000

int main(void) {
    char texto_base[] = "abcdefghijklmnopqrstuvwxyz 1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int *indice = (int *)malloc(sizeof(int));
    *indice = 0;
    struct timeval tv;
    int number, tmp_index, i, cont = 0;

    #pragma omp parallel for num_threads(3) private(tv, number, tmp_index, i)
    for (cont = 0; cont < MAX; cont++) {
        #pragma omp critical
        {
            gettimeofday(&tv, NULL);
            number = ((tv.tv_usec / 47) % 3) + 1;
            tmp_index = *indice;
            for (i = 0; i < number; i++)
            if (!(tmp_index + i > sizeof(texto_base)))
            fprintf(stderr,"%c", texto_base[tmp_index + i]);
            *indice = tmp_index + i;
            if (tmp_index + i > sizeof(texto_base)) {
                fprintf(stderr,"\n");
                *indice = 0;
            }
        }
    }
    printf("\n");
    free(indice);
    return 0;
}
