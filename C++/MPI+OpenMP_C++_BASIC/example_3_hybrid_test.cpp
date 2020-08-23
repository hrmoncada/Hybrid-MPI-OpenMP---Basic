/*
On the HPC you need the modules
module load openmpi

Options are similar to running an MPI job, with some differences, e.g.
--np=4                    Specifies the number of MPI processes (“tasks”), for this case 4 task.
OMP_NUM_THREADS=8         Allocates 8 CPUs for each task, for this case 8 threads. 
 

Compile :
$ mpic++ -fopenmp -o out  example_3_hybrid_test.cpp 

or

$ mpicxx -fopenmp -o out  example_3_hybrid_test.cpp 

Setting the Number of Threads Using an OpenMP Environment Variable
export OMP_NUM_THREADS=2

Execute:
$ mpirun -np 4 ./out 
Invalid MIT-MAGIC-COOKIE-1 keyMPI rank: MPI rank: 00 with thread ID: 0 with thread ID: 1

MPI rank: 1 with thread ID: 0
MPI rank: 2 with thread ID: 0
MPI rank: 3 with thread ID: 0
MPI rank: 2 with thread ID: 1

Slurm (workload manager):
1. -c, --cpus-per-task=<ncpus> Request that ncpus be allocated per process
2. srun option --mpi= (or the equivalent environment variable SLURM_MPI_TYPE can be used to specify when a different MPI implementation is to be supported for an individual job).

$ mpirun -np 4 ./out --cpus-per-task=4 --mpi=pmix
Invalid MIT-MAGIC-COOKIE-1 keyMPI rank: 0 with thread ID: 0 on Fiona
MPI rank: 0 with thread ID: 1 on Fiona
MPI rank: MPI rank: 11 with thread ID: 1 on Fiona with thread ID: 
MPI rank: 1 with thread ID: 1 on Fiona
MPI rank: 2 with thread ID: 0 on Fiona
0 on Fiona
MPI rank: 3 with thread ID: 0 on Fiona
MPI rank: 3 with thread ID: 1 on Fiona

Note:
The whole process set: 4 MPI task with 2 openMP threas for MPI task

MPI_THREAD_MULTIPLE : Multiple threads may call MPI, with no restrictions.These values are monotonic; i.e., MPI_THREAD_SINGLE < MPI_THREAD_FUNNELED < MPI_THREAD_SERIALIZED < MPI_THREAD_MULTIPLE. Different processes in MPI_COMM_WORLD may require different levels of thread support.
 */

#include <iostream>
#include <mpi.h>
#include <omp.h>
using namespace std;
int main(int argc, char** argv){
  int my_rank, num_procs, namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int thread_id, nthreads;
  int i, j, provided;

/* Initialize MPI Environment */  
  MPI_Init_thread(&argc,&argv, MPI_THREAD_MULTIPLE, &provided);
  
  /* Get the total number of processors. I am asking for */  
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  
/* Get current process ID number (my_rank) */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
/* Get the name of this processor (usually the hostname) */  
  MPI_Get_processor_name(processor_name, &namelen);
  
#pragma omp parallel private( thread_id )
  {
    thread_id = omp_get_thread_num();
    nthreads = omp_get_num_threads();
    
    for ( i = 0; i <= num_procs - 1; i++ ){
      MPI_Barrier(MPI_COMM_WORLD);
      for ( j = 0; j <= nthreads - 1; j++ ){
        if ( (i == my_rank) && (j == thread_id) ){
          cout << "MPI rank: " << my_rank << " with thread ID: " << thread_id << " on " <<  processor_name << endl;
        }
      }
    }
  }
  
/* End MPI Environment */
  MPI_Finalize();
  return 0;
}
