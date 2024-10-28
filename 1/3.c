#include <stdio.h>

double cbrt(double a);

int main() {
    double a, b, c;

    printf("enter first number: ");
    scanf("%lf", &a);
    printf("enter second number: ");
    scanf("%lf", &b);
    printf("enter third number: ");
    scanf("%lf", &c);

    if (a != 0 && b != 0 && c != 0)
        printf("geometric mean: %lf\n", cbrt(a * b * c));
    else
        printf("arithmetic mean: %lf\n", (a + b + c) / 3);
}

/*
 * calculate cubic root of a number using Newton's method.
 *
 * x -= ((x * x * x) - a) / (3 * x * x)
 */
double cbrt(double a) {
    if (a == 0 || a == 1 || a == -1)
        return a;

    double x = 1;
    for (char i = 0; i < 50; i++)
        x = (1.0 / 3.0) * (2 * x + a / (x * x));

    return x;
}
