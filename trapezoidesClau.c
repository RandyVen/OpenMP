#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void trapezoide(double a, double b, int n, double *global_result_p);

double f(double x);

double get_wall_time();

int main(int argc, char **argv)
{
    double global_result = 0.0;
    double a, b;
    int n;
    int thread_count;

    thread_count = strtol(argv[1], NULL, 10);
    printf("Ingrese a, b, n, numero de hilos\n");
    scanf("%lf %lf %d %d", &a, &b, &n, &thread_count);

    double start_time = get_wall_time();

#pragma omp parallel num_threads(thread_count) reduction(+ : global_result)
    {
        trapezoide(a, b, n, &global_result);
    }

    printf("Con n = %d trapezoides, nuestra estimacion\n", n);
    printf("de la integral de %f a %f = %.14e\n", a, b, global_result);

    double end_time = get_wall_time();
    double execution_time = end_time - start_time;

    printf("Tiempo de ejecucion: %.6f segundos\n", execution_time);

    return 0;
}

void trapezoide(double a, double b, int n, double *global_result_p)
{
    double h, x, my_result;
    double local_a, local_b;
    int i, local_n;
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    h = (b - a) / n;
    local_n = n / thread_count;
    local_a = a + my_rank * local_n * h;
    local_b = local_a + local_n * h;
    my_result = (f(local_a) + f(local_b)) / 2.0;
    for (i = 1; i <= local_n - 1; i++)
    {
        x = local_a + i * h;
        my_result += f(x);
    }
    my_result = my_result * h;

    *global_result_p += my_result;
}

double f(double x)
{
    double return_val;

    return_val = x * x;

    return return_val;
}

double get_wall_time()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * 0.000001;
}
