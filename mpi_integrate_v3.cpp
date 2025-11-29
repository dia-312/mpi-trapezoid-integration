// mpi_integrate_v3.cpp
// MPI trapezoid integration - version 3 (MPI_Reduce collective)
#include <iostream>
#include <cstdlib>
#include <mpi.h>
using namespace std;

float func(float x);

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double total_start = MPI_Wtime();

    double init_start = MPI_Wtime();
    if (argc != 4) {
        if (rank == 0) cout << "Usage: " << argv[0] << " a b n\n";
        MPI_Finalize();
        return 1;
    }
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = atoi(argv[3]);
    double h = (b - a) / n;

    int q = n / size;
    int r = n % size;
    int local_n = (rank < r) ? (q + 1) : q;
    int start_index = rank * q + (rank < r ? rank : r);
    double local_a = a + start_index * h;
    double local_b = local_a + local_n * h;
    double init_end = MPI_Wtime();

    double compute_start = MPI_Wtime();
    double local_sum = 0.0;
    if (local_n > 0) {
        local_sum = (func((float)local_a) + func((float)local_b)) / 2.0;
        for (int i = 1; i < local_n; i++) {
            double x = local_a + i * h;
            local_sum += func((float)x);
        }
    }
    double local_integral = h * local_sum;
    double compute_end = MPI_Wtime();

    double comm_start = MPI_Wtime();
    double total = 0.0;
    MPI_Reduce(&local_integral, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    double comm_end = MPI_Wtime();
    double total_end = MPI_Wtime();

    cout.setf(std::ios::fixed); cout.precision(6);
    cout << "Process " << rank << " | Init: " << (init_end - init_start)
         << " s | Compute: " << (compute_end - compute_start)
         << " s | Comm: " << (comm_end - comm_start)
         << " s | Total: " << (total_end - total_start) << " s\n";

    if (rank == 0) {
        cout << "Result = " << total << "\n";
    }

    MPI_Finalize();
    return 0;
}
