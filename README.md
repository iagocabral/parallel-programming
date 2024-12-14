# Parallel Programming Repository

This repository contains practical examples of parallel programming in C, utilizing libraries such as OpenMP, MPI, and CUDA. These examples demonstrate concepts like threads, processes, and GPU acceleration to optimize application performance.

## Contents

- **OpenMP Examples**: Demonstrates shared-memory parallelism using OpenMP directives.
- **MPI Examples**: Illustrates distributed-memory parallelism with the Message Passing Interface.
- **CUDA Examples**: Showcases GPU acceleration techniques using NVIDIA's CUDA platform.

## Requirements

- **C Compiler**: Ensure that a C compiler (e.g., GCC) is installed on your system.
- **OpenMP**: Verify that your compiler supports OpenMP.
- **MPI Library**: Install an MPI implementation such as MPICH or OpenMPI.
- **CUDA Toolkit**: For CUDA examples, install the NVIDIA CUDA Toolkit and ensure your system has a compatible NVIDIA GPU.

## Compilation and Execution


### For OpenMP programs:
```
gcc -fopenmp example.c -o example
```

