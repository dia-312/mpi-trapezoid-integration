// integrate.cpp
// Serial trapezoid integration with timing (init, compute, comm, total)
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

float func(float x);

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " a b n\n";
        return 1;
    }

    clock_t t_total_start = clock();

    clock_t t_init_start = clock();
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = atoi(argv[3]);
    double h = (b - a) / n;
    clock_t t_init_end = clock();

    clock_t t_compute_start = clock();
    // trapezoid rule
    double sum = (func((float)a) + func((float)b)) / 2.0;
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += func((float)x);
    }
    double integral = h * sum;
    clock_t t_compute_end = clock();

    clock_t t_comm_start = clock();
    // no communication in serial version
    clock_t t_comm_end = clock();

    clock_t t_total_end = clock();

    double init_time = double(t_init_end - t_init_start) / CLOCKS_PER_SEC;
    double compute_time = double(t_compute_end - t_compute_start) / CLOCKS_PER_SEC;
    double comm_time = double(t_comm_end - t_comm_start) / CLOCKS_PER_SEC;
    double total_time = double(t_total_end - t_total_start) / CLOCKS_PER_SEC;

    cout.setf(std::ios::fixed); cout.precision(6);
    cout << "Init: " << init_time << " s | Compute: " << compute_time
         << " s | Comm: " << comm_time << " s | Total: " << total_time << " s\n";
    cout << "Result = " << integral << "\n";

    return 0;
}
