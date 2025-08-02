#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 200
#define SCALAR 5

void staticSchedule(int chunk, int num_threads) {
    int A[SIZE];
    for (int i = 0; i < SIZE; i++) A[i] = i;

    double start = omp_get_wtime();

    omp_set_num_threads(num_threads);
    #pragma omp parallel for schedule(static, chunk)
    for (int i = 0; i < SIZE; i++) {
        A[i] += SCALAR;
    }

    double end = omp_get_wtime();
    printf("STATIC | Threads: %d | Chunk: %d | Time: %f seconds\n", num_threads, chunk, end - start);
}

void dynamicSchedule(int chunk, int num_threads) {
    int A[SIZE];
    for (int i = 0; i < SIZE; i++) A[i] = i;

    double start = omp_get_wtime();

    omp_set_num_threads(num_threads);
    #pragma omp parallel for schedule(dynamic, chunk)
    for (int i = 0; i < SIZE; i++) {
        A[i] += SCALAR;
    }

    double end = omp_get_wtime();
    printf("DYNAMIC | Threads: %d | Chunk: %d | Time: %f seconds\n", num_threads, chunk, end - start);
}

void demonstrateNowait(int num_threads) {
    int A[SIZE], B[SIZE];
    for (int i = 0; i < SIZE; i++) {
        A[i] = i;
        B[i] = i;
    }

    omp_set_num_threads(num_threads);
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for schedule(static, 10) nowait
        for (int i = 0; i < SIZE; i++) {
            A[i] += SCALAR;
        }

        #pragma omp for schedule(static, 10)
        for (int i = 0; i < SIZE; i++) {
            B[i] *= 2;
        }
    }

    double end = omp_get_wtime();
    printf("NOWAIT DEMO | Threads: %d | Time: %f seconds\n", num_threads, end - start);
}

int main() {
    int chunks[] = {1, 5, 10, 20, 50};
    int thread_counts[] = {2, 4, 8};

    for (int t = 0; t < 3; t++) {
        int threads = thread_counts[t];
        for (int i = 0; i < 5; i++) {
            int chunk = chunks[i];
            staticSchedule(chunk, threads);
            dynamicSchedule(chunk, threads);
            printf("\n");
        }
        demonstrateNowait(threads);
        printf("\n-------------------------------\n\n");
    }

    return 0;
}

