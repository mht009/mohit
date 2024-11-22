#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int n = 100;  // Total number of elements
    int *arr = NULL;
    int *sub_arr = NULL;
    int local_sum = 0;
    int total_sum = 0;
    double average = 0.0;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Allocate the array and initialize values only on rank 0
    if (rank == 0) {
        arr = (int*)malloc(n * sizeof(int));
        // Fill array with values: 1, 2, 3, ..., n
        for (int i = 0; i < n; i++) {
            arr[i] = i + 1;
        }
    }

    // Allocate space for each process to store its portion of the array
    int local_n = n / size; // Each process gets roughly n/size elements
    sub_arr = (int*)malloc(local_n * sizeof(int));

    // Timing variables
    double scatter_start, scatter_end;
    double reduce_start, reduce_end;
    double local_sum_start, local_sum_end;

    // Scatter the array to all processes
    scatter_start = MPI_Wtime();  // Start timing scatter
    MPI_Scatter(arr, local_n, MPI_INT, sub_arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);
    scatter_end = MPI_Wtime();    // End timing scatter

    // Print the elements received by each process in a row (without indices)
    printf("Process %d received the following elements: ", rank);
    for (int i = 0; i < local_n; i++) {
        printf("%d ", sub_arr[i]);
    }
    printf("\n");

    // Compute the local sum
    local_sum_start = MPI_Wtime();  // Start timing local sum computation
    for (int i = 0; i < local_n; i++) {
        local_sum += sub_arr[i];
    }
    local_sum_end = MPI_Wtime();    // End timing local sum computation

    // Reduce the local sums to compute the total sum at rank 0
    reduce_start = MPI_Wtime();  // Start timing reduce
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    reduce_end = MPI_Wtime();    // End timing reduce

    // Print the times for each process
    printf("Process %d:\n  Scatter time: %.6f seconds\n  Local sum computation time: %.6f seconds\n  Reduce time: %.6f seconds\n", rank, scatter_end - scatter_start, local_sum_end - local_sum_start, reduce_end - reduce_start);

    // Compute the average at rank 0
    if (rank == 0) {
        average = (double)total_sum / n;
        printf("The average is: %.2f\n", average);
    }

    // Free the allocated arrays
    free(sub_arr);
    if (rank == 0) {
        free(arr);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}

