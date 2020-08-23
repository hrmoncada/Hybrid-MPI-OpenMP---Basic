! On the HPC you need the modules
! module load openmpi
! 
! Options are similar to running an MPI job, with some differences, e.g.
! --np=4                    Specifies the number of MPI processes (“tasks”), for this case 4 task.
! OMP_NUM_THREADS=8         Allocates 8 CPUs for each task, for this case 8 threads. 
!  
! 
! Compile :
! $ mpifort -fopenmp -o out  example_3_hybrid_test.f90
! 
! Setting the Number of Threads Using an OpenMP Environment Variable
! export OMP_NUM_THREADS=2
! 
! Execute:
! $ mpirun -np 4 ./out 
! Invalid MIT-MAGIC-COOKIE-1 keyMPI rank: MPI rank: 00 with thread ID: 0 with thread ID: 1
! 
! MPI rank: 1 with thread ID: 0
! MPI rank: 2 with thread ID: 0
! MPI rank: 3 with thread ID: 0
! MPI rank: 2 with thread ID: 1
! 
! Slurm (workload manager):
! 1. -c, --cpus-per-task=<ncpus> Request that ncpus be allocated per process
! 2. srun option --mpi= (or the equivalent environment variable SLURM_MPI_TYPE can be used to specify when a different MPI implementation is to be supported for an individual job).
! 
! $ mpirun -np 4 ./out --cpus-per-task=4 --mpi=pmix
! Invalid MIT-MAGIC-COOKIE-1 keyMPI rank: 0 with thread ID: 0 on Fiona
! MPI rank: 0 with thread ID: 1 on Fiona
! MPI rank: MPI rank: 11 with thread ID: 1 on Fiona with thread ID: 
! MPI rank: 1 with thread ID: 1 on Fiona
! MPI rank: 2 with thread ID: 0 on Fiona
! 0 on Fiona
! MPI rank: 3 with thread ID: 0 on Fiona
! MPI rank: 3 with thread ID: 1 on Fiona
! 
! Note:
! The whole process set: 4 MPI task with 2 openMP threas for MPI task
! 
! MPI_THREAD_MULTIPLE : Multiple threads may call MPI, with no restrictions.These values are monotonic; i.e., MPI_THREAD_SINGLE < MPI_THREAD_FUNNELED < MPI_THREAD_SERIALIZED < MPI_THREAD_MULTIPLE. Different processes in MPI_COMM_WORLD may require different levels of thread support.

program hybrid_test
  implicit none
  include "mpif.h"
  integer(4) :: i, j, ierr
  integer(4) :: my_rank, num_procs
  integer(4) :: nthreads, thread_id
  integer(4) :: omp_get_num_threads, omp_get_thread_num
 
! Initialize MPI Environment 
  call MPI_INIT(ierr)
  
! Get the total number of processors. I am asking for  
  call MPI_COMM_SIZE(MPI_COMM_WORLD,num_procs,ierr)
  
! Get current process ID number (my_rank)
  call MPI_COMM_RANK(MPI_COMM_WORLD,my_rank,ierr)
  
!$omp parallel private( thread_id )
  thread_id = omp_get_thread_num()
  nthreads = omp_get_num_threads()

  do i = 0, num_procs-1
     call MPI_BARRIER(MPI_COMM_WORLD,ierr)
     do j = 0, nthreads-1
         if ( i == my_rank  .and. j == thread_id  ) then       
            print *, "MPI rank:", my_rank, " with thread ID:", thread_id
        end if
     end do
  end do
!$omp end parallel

! End MPI Environment
  call MPI_FINALIZE(ierr)
  stop
  
end program hybrid_test
