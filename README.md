# Hybrid MPI+OpenMP-Basic
**MPI** is a standardized library (not a language) for the collection of processes communicating via messages passing.
**OpenMP** is an API for shared-memory programming that includes compiler directives, library routines, and environment variables.

A hybrid **MPI + OpenMP** implementation of an application might be beneficial because it reduces the memory requirements of an application, and improves its performance.

* Introducing MPI into OpenMP applications can help scale across multiple Symmetric multiprocessing (SMP) nodes.
* Introducing OpenMP into MPI applications can help make more efficient use of the shared memory on Symmetric multiprocessing (SMP) nodes, thus mitigating the need for explicit intra-node communication.
* Introducing MPI and OpenMP during the design/coding of a new application can help maximize efficiency, performance, and scaling.

## Table of Contents
- [LaTeX-Presentation](#LaTeX-Presentation)
- [Code](#Code)
  * [C](#C)
  * [C++](#C)
  * [Fortran](#Fortran)
<!-- 
    + [Sub-sub-heading](#sub-sub-heading-1)
-->
- [Rules](#Rules)

<!-- Comments -->
## Rules
Here are the rules for (or lack thereof):
   1. Push changes directly to head of https://github.com/hrmoncada/Hybrid-MPI-OpenMP-Basic
   2. No pull requests or reviews are needed, unless you would like one. This means that personal forks of /Hybrid-MPI-OpenMP-Basic are not needed.
   3. Only restriction is to not overwrite files others have uploaded, without asking them.
   4. Scripts are not required to work in any particular way. The purpose is for the convenience of sharing scripts of any kind. Scripts do not come with any guarantees.
   5. Files may include everything, such as source code, source binary, figures and grapghics.
   6. Files should generally be a few MB or less. If a single file is larger than 2 to 5 MB, please keep some graphics as examples, keep the code, but clear the remaining graphics before saving.
   7. When the repository becomes too large (>~100MB) we reserve the right to purge the history in order to reduce the size.
