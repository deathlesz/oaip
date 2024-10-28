#include <stdio.h>

int main() {
    double a, b, c;

    printf("enter first number: ");
    scanf("%lf", &a);
    printf("enter second number: ");
    scanf("%lf", &b);
    printf("enter third number: ");
    scanf("%lf", &c);

    if (a == b || b == c || a == c)
        puts("there is at least 1 pair of equal numbers");
    else {
        puts("there are no equal numbers");
        printf("%lf", a);
    }
}
