/*
On the HPC you need the modules
module load openmpi

Options are similar to running an MPI job, with some differences, e.g.
--np=4                    Specifies the number of MPI processes (“tasks”), for this case 4 task.
OMP_NUM_THREADS=8         Allocates 8 CPUs for each task, for this case 8 threads. 
 

Compile :
mpicc -fopenmp -o out  example_1_Hello_World_Hybrid.c

Setting the Number of Threads Using an OpenMP Environment Variable
export OMP_NUM_THREADS=2

Execute:
mpirun -np 4 ./out

Hello from thread 0 out of 2 from process 0 out of 4 on Fiona
Hello from thread 1 out of 2 from process 0 out of 4 on Fiona
Hello from thread 0 out of 2 from process 2 out of 4 on Fiona
Hello from thread 1 out of 2 from process 2 out of 4 on Fiona
Hello from thread 0 out of 2 from process 3 out of 4 on Fiona
Hello from thread 0 out of 2 from process 1 out of 4 on Fiona
Hello from thread 1 out of 2 from process 3 out of 4 on Fiona
Hello from thread 1 out of 2 from process 1 out of 4 on Fiona

the whole process set: 4 MPI task with 2 openMP threas for MPI task
 */
#include <stdio.h>

/* Include MPI and OpenMP Header File */
#include "mpi.h"
#include <omp.h>


int main(int argc, char *argv[]) {
  int num_procs, my_rank, namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int thead_id = 0, nthreads = 1;
  
/* Initialize MPI Environment */
  MPI_Init(&argc, &argv);
  
/* Get the total number of processors. I am asking for */  
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  
/* Get current process ID number (my_rank) */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
/* Get the name of this processor (usually the hostname) */  
  MPI_Get_processor_name(processor_name, &namelen);

  #pragma omp parallel default(shared) private(thead_id, nthreads)
  {
    nthreads = omp_get_num_threads();
    thead_id = omp_get_thread_num();
    printf("Hello from thread %d out of %d from process %d out of %d on %s\n",
           thead_id, nthreads, my_rank, num_procs, processor_name);
  }
  
/* End MPI Environment */
  MPI_Finalize();
}
