#include <stdio.h>

int main() {
    int n = 2, a = 0, b = 1;

    printf("enter n (n > 1, n is fibbonachi number): ");
    while (scanf("%d", &n) != 1 || !(n > 1)) {
        printf("invalid input! try again: ");
        while (getchar() != '\n');
    }

    int temp;
    while (b < n) {
        temp = b;
        b = a + b;
        a = temp;
    }

    int corrected = n;
    if (n != b) {
        corrected = (n - a) < (b - n) ? a : b;

        printf("[!] you didn't enter a fibbonachi number\n[:] closest "
               "fibbonachi number to the one you entered is %d\n[!] answer is "
               "given using n = %d\n\n",
               corrected, corrected);
    }

    printf("[+] previous fibbonachi number: %d\n",
           (corrected >= n) ? a : b - a);
    printf("[+] next fibbonachi number: %d\n", (corrected >= n) ? a + b : b);
}
