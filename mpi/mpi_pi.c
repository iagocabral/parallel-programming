#include <stdio.h>
#include <mpi.h>

#define NUM_STEPS 8000000

int main(int argc, char *argv[]) {
    int rank, size;
    double step, sum = 0.0, partial_sum = 0.0;
    double x, pi;

    // Inicialização do MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Define o tamanho do passo
    step = 1.0 / (double) NUM_STEPS;

    // Cada processo realiza parte do cálculo
    for (int i = rank; i < NUM_STEPS; i += size) {
        x = (i + 0.5) * step;
        partial_sum += 4.0 / (1.0 + x * x);
    }

    // Reduz as somas parciais de todos os processos no processo 0
    MPI_Reduce(&partial_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // O processo 0 calcula o valor final de π e o imprime
    if (rank == 0) {
        pi = sum * step;
        printf("Pi = %.15f\n", pi);
    }

    // Finaliza o MPI
    MPI_Finalize();
    return 0;
}
