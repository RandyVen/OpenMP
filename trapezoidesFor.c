#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

double trapezoide(double a, double b, int n, int thread_count);

double f(double x);

double get_wall_time();

int main(int argc, char **argv)
{
    double a, b;
    int n;
    int thread_count;

    thread_count = strtol(argv[1], NULL, 10);
    printf("Ingrese a, b, n, numero de hilos\n");
    scanf("%lf %lf %d %d", &a, &b, &n, &thread_count);

    double start_time = get_wall_time();

    double integral = trapezoide(a, b, n, thread_count);

    printf("Con n = %d trapezoides, nuestra estimacion\n", n);
    printf("de la integral de %f a %f = %.14e\n", a, b, integral);

    double end_time = get_wall_time();
    double execution_time = end_time - start_time;

    printf("Tiempo de ejecucion: %.6f segundos\n", execution_time);

    return 0;
}

double trapezoide(double a, double b, int n, int thread_count)
{
    double integral, h;
    int k;
    double sum = 0.0;

    h = (b - a) / n;

#pragma omp parallel for num_threads(thread_count) reduction(+ : sum)
    for (k = 1; k <= n - 1; k++)
    {
        double x = a + k * h;
        sum += f(x);
    }

    integral = h * ((f(a) + f(b)) / 2.0 + sum);

    return integral;
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
