/*----------------------------------------------
 * riemann.c - calculo de area bajo la curva
 *----------------------------------------------
 * Sumas de Riemann para calcular la integral f(x)
 *
 * Date:  2021-09-22
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A 1
#define B 40
#define N 10e6

double f(double x); // La funcion a integrar
double trapezoides(double a, double b, int n);

int main(int argc, char *argv[])
{
    double integral;
    double a = A, b = B;
    int n = N;
    double h;

    if (argc > 2)
    {
        a = strtol(argv[1], NULL, 10);
        b = strtol(argv[2], NULL, 10);
    }

    clock_t start = clock();

    //---- Aproximacion de la integral
    integral = trapezoides(a, b, n);

    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Con n = %d trapezoides, nuestra aproximacion \n", n);
    printf("de la integral de %f a %f es = %.10f\n", a, b, integral);
    printf("Tiempo de ejecución: %.2f segundos\n", cpu_time_used);

    return 0;
}

//------------------------------------------
// trapezoides
//
// Estimar la integral mediante sumas de Riemann
// Input: a,b,n,h
// Output: integral
//------------------------------------------
double trapezoides(double a, double b, int n)
{
    double integral, h;
    int k;

    //---- Ancho de cada trapezoide
    h = (b - a) / n;
    //---- Valor inicial de la integral (valores extremos)
    integral = (f(a) + f(b)) / 2.0;

    for (k = 1; k <= n - 1; k++)
    {
        integral += f(a + k * h);
    }
    integral = integral * h;

    return integral;
} /*trapezoides*/

//------------------------------------------
// f
//
// Funcion a ser integrada
// Input: x
//------------------------------------------
double f(double x)
{
    double return_val;

    return_val = x * x;

    return return_val;
} /*f*/
