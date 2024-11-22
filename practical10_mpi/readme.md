mpicc scatter_reduce_openmpi.c -o scatter_reduce_openmpi

mpirun -np 4 ./scatter_reduce_openmpi

