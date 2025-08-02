#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void matrixAddition(int size, int num_threads) {

    int **A = malloc(size * sizeof(int *));
    int **B = malloc(size * sizeof(int *));
    int **C = malloc(size * sizeof(int *));

    for (int i = 0; i < size; i++) {
        A[i] = malloc(size * sizeof(int));
        B[i] = malloc(size * sizeof(int));
        C[i] = malloc(size * sizeof(int));
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    double start = omp_get_wtime();

    #pragma omp parallel for collapse(2) num_threads(num_threads)
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];

    double end = omp_get_wtime();

    printf("Matrix Size: %d x %d | Threads: %d | Time: %f seconds\n", size, size, num_threads, end - start);

    for (int i = 0; i < size; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A); free(B); free(C);
}


int main()
{
	int sizes[]={250,500,750,1000,2000};
	int threads[]={1,2,4,8};
	for(int s=0;s<5;s++)
	{
		for(int t=0;t<4;t++)
		{
			matrixAddition(sizes[s],threads[t]);
		}
		printf("\n");
	}
}
