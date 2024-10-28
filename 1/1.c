#include <stdio.h>

double sqrt(double a);

int main() {
    double x1, y1, x2, y2;

    printf("enter x1: ");
    scanf("%lf", &x1);
    printf("enter y1: ");
    scanf("%lf", &y1);
    printf("enter x2: ");
    scanf("%lf", &x2);
    printf("enter y2: ");
    scanf("%lf", &y2);

    double xdiff = x1 - x2;
    double ydiff = y1 - y2;
    double result = sqrt(xdiff * xdiff + ydiff * ydiff);

    printf("distance between two points: %.2lf\n", result);
}

/*
 * calculate square root of a number using Newton's method;
 * !!! doesn't handle negative numbers
 *
 * x -= ((x * x) - a) / (2 * x) -- without factorization
 */
double sqrt(double a) {
    if (a == 0 || a == 1)
        return a;

    double x = 1;
    for (char i = 15; i > 0; i--)
        x = (1.0 / 2.0) * (x + a / x);

    return x;
}
