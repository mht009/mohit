#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ARRAY_SIZE 16  // Define array size

// Function to find mean
double findMean(int* array, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

// Function to find median
double findMedian(int* array, int size) {
    // Sort array (simple bubble sort)
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    if (size % 2 == 0) {
        return (array[size / 2 - 1] + array[size / 2]) / 2.0;
    } else {
        return array[size / 2];
    }
}

// Function to find mode
int findMode(int* array, int size) {
    int mode = array[0];
    int maxCount = 0;
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (array[j] == array[i])
                count++;
        }
        if (count > maxCount) {
            maxCount = count;
            mode = array[i];
        }
    }
    return mode;
}

int main(int argc, char** argv) {
    int rank, size;
    int data[ARRAY_SIZE] = {49, 37, 80, 7, 24, 70, 78, 9, 45, 26, 68, 34, 92, 10, 56, 15};
    int local_data[ARRAY_SIZE];
    int local_sum = 0, total_sum = 0;
    
    double start_time, end_time;
    double scatter_time, local_sum_time, reduce_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Start measuring total execution time
    start_time = MPI_Wtime();

    int elements_per_process = ARRAY_SIZE / size;

    // Measure scatter time
    double scatter_start = MPI_Wtime();
    MPI_Scatter(data, elements_per_process, MPI_INT, local_data, elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);
    double scatter_end = MPI_Wtime();
    scatter_time = scatter_end - scatter_start;

    // Measure local sum time
    double local_sum_start = MPI_Wtime();
    for (int i = 0; i < elements_per_process; i++) {
        local_sum += local_data[i];
    }
    double local_sum_end = MPI_Wtime();
    local_sum_time = local_sum_end - local_sum_start;

    // Measure reduce time
    double reduce_start = MPI_Wtime();
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    double reduce_end = MPI_Wtime();
    reduce_time = reduce_end - reduce_start;

    // End measuring total execution time
    end_time = MPI_Wtime();
    double total_execution_time = end_time - start_time;

    // Root process prints the final result
    if (rank == 0) {
        printf("Data array: ");
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");

        printf("Total sum of the elements is: %d\n", total_sum);

        // Finding mean, median, and mode
        double mean = findMean(data, ARRAY_SIZE);
        double median = findMedian(data, ARRAY_SIZE);
        int mode = findMode(data, ARRAY_SIZE);

        printf("Mean: %.2f\n", mean);
        printf("Median: %.2f\n", median);
        printf("Mode: %d\n", mode);
        printf("Total execution time: %f seconds\n", total_execution_time);
    }

    // Print time statistics for each rank
    printf("Rank %d - Scatter Time: %f seconds, Local Sum Time: %f seconds, Reduce Time: %f seconds\n",
           rank, scatter_time, local_sum_time, reduce_time);

    MPI_Finalize();
    return 0;
}

