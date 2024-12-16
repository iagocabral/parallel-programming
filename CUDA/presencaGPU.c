#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main (int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Sintaxe: %s <no do device GPU id>\n", argv[O]);
        exit (1);
    }
    int devId = atoi(argv [1]);
    cudaSetDevice(devId);
    cudaDeviceProp prop;
    cudaGetDeviceProperties (&prop, devId);
    printf("\bDevice: &s\n", prop.name);
    return 0;
}
