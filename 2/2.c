#include <stdio.h>

int main() {
    int n = 1;
    double result = 0;

    printf("enter n (n > 1): ");
    while (scanf("%d", &n) != 1 || n < 1) {
        printf("invalid input! try again: ");
        while (getchar() != '\n');
    }

    do result += 1.0 / n;
    while (--n);

    printf("B = %lf\n", result);
}
