🧩 MPI Trapezoid Integration (Serial + MPI Versions)

A high-performance numerical integration project implementing the Trapezoidal Rule in both serial and parallel (MPI) versions.
The goal is to compute the definite integral of a polynomial function and compare execution times across different communication strategies in MPI.

📌 Overview

This project computes the numerical integration of:
<img width="225" height="48" alt="image" src="https://github.com𝑓
(/user-attachments/assets/aeb439ca-2860-466a-9d6b-a2eb1aef8455" />


using the Trapezoid Rule, implemented in four versions:

✔ Serial Implementation → integrate.cpp
✔ MPI – Version 1 (Ordered Recv) → mpi_integrate_v1.cpp
✔ MPI – Version 2 (ANY_SOURCE Recv) → mpi_integrate_v2.cpp
✔ MPI – Version 3 (Collective Reduce) → mpi_integrate_v3.cpp

Each version measures execution breakdown:

Init Time

Compute Time

Communication Time

Total Time

The goal is to evaluate parallel performance, communication overhead, and scalability.

📁 File Structure
mpi-trapezoid-integration/
│
├── integrate.cpp           # Serial trapezoid integration
├── mpi_integrate_v1.cpp    # MPI – point-to-point (ordered receive)
├── mpi_integrate_v2.cpp    # MPI – point-to-point (MPI_ANY_SOURCE)
├── mpi_integrate_v3.cpp    # MPI – collective reduction (MPI_Reduce)
│
├── func.cpp                # f(x) = x^2 + 3x + 10
├── integrate.txt           # Assignment description + pseudocode
│
└── Makefile                # Build and run commands

🔧 Building the Project

Compile everything using the provided Makefile:

make


This generates:

integrate
mpi_integrate_v1
mpi_integrate_v2
mpi_integrate_v3


Clean the build:

make clean

▶️ Running the Programs
Serial Version
./integrate a b n


Example:

./integrate 1 4 1000000

MPI Version 1 — Ordered Recv
mpirun -np 4 ./mpi_integrate_v1 a b n

MPI Version 2 — ANY_SOURCE Recv
mpirun -np 4 ./mpi_integrate_v2 a b n

MPI Version 3 — MPI_Reduce
mpirun -np 4 ./mpi_integrate_v3 a b n


Example:

mpirun -np 6 ./mpi_integrate_v3 1 4 1000000

🧮 Trapezoid Rule Recap

For interval [a, b] divided into n slices:

<img width="479" height="136" alt="image" src="https://github.com/user-attachments/assets/a4d08bbc-95b2-4aa1-bf15-1d55dcd5b00b" />


Parallelization splits n across MPI processes, each computing a partial integral.

🔍 MPI Communication Strategies
✔ Version 1 (v1): Ordered Receive

Master receives results strictly from processes 1 → p-1.

✔ Version 2 (v2): ANY_SOURCE

Master receives results from whichever process finishes sooner.

✔ Version 3 (v3): Collective Reduce

All processes directly contribute using:

MPI_Reduce(&local, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


⭐ This is the fastest and cleanest version.

🧪 Performance Metrics

Each process prints:

Init time

Compute time

Communication time

Total execution time

Expected behavior:

Processes	Expected Speedup
1	≈ serial
2	1.8× faster
4	3–3.5× faster
8	diminishing returns due to comm overhead
📊 Suggested Experiments

Run with large n such as:

n = 10,000,000
np = 1, 2, 4, 6, 8


Compare:

v1 (slowest)

v2 (better for unbalanced workloads)

v3 (best overall)

Plot Compute vs Communication time to analyze scaling.

🚀 Future Improvements

Add OpenMP hybrid version

Use MPI_Scatter + MPI_Gather instead of manual partitioning

Add adaptive mesh refinement

Support piecewise integrand functions

Output CSV logs for plotting speedup curves

👤 Author

Dia Arar
MPI Trapezoid Integration
An-Najah National University

<p align="center"><b>⭐ If you like this project, consider starring the repository!</b></p>
