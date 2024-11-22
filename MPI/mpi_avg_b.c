#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int n = 100;  // Total number of elements
    int *arr = NULL;
    int local_sum = 0;
    int total_sum = 0;
    double average = 0.0;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Allocate space for the array on all processes
    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Initialize the array only on the root process
    if (rank == 0) {
        printf("Array broadcasted: ");
        // Fill array with values: 1, 2, 3, ..., n
        for (int i = 0; i < n; i++) {
            arr[i] = i + 1;
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    // Broadcast the entire array to all processes
    double scatter_start = MPI_Wtime();  // Start timing broadcast
    MPI_Bcast(arr, n, MPI_INT, 0, MPI_COMM_WORLD);  // Broadcast the array
    double scatter_end = MPI_Wtime();    // End timing broadcast

    // Compute the local sum for each process (sum its part)
    int local_n = n / size;  // Each process gets roughly n/size elements
    int start_idx = rank * local_n;
    int end_idx = (rank == size - 1) ? n : (rank + 1) * local_n;  // Handle the case when n is not perfectly divisible by size

    double local_sum_start = MPI_Wtime();  // Start timing local sum computation
    for (int i = start_idx; i < end_idx; i++) {
        local_sum += arr[i];
    }
    double local_sum_end = MPI_Wtime();    // End timing local sum computation

    // Reduce the local sums to compute the total sum at rank 0
    double reduce_start = MPI_Wtime();  // Start timing reduce
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    double reduce_end = MPI_Wtime();    // End timing reduce

    // Print the times for each process
    printf("Process %d:\n  Scatter time: %.6f seconds\n  Local sum computation time: %.6f seconds\n  Reduce time: %.6f seconds\n", rank, scatter_end - scatter_start, local_sum_end - local_sum_start, reduce_end - reduce_start);


    // Compute the average at rank 0
    if (rank == 0) {
        average = (double)total_sum / n;
        printf("The average is: %.2f\n", average);
    }

    // Free the allocated array only on the root process
    if (rank == 0) {
        free(arr);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}

