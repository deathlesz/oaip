#include <stdio.h>

int main() {
    // we loop separately over tens place and ones place
    for (int a = 1; a < 10; a++) {
        for (int b = 0; b < 10; b++) {
            if (a + b == 11 && 10 * a + b + 27 == 10 * b + a) {
                printf("[+] number is %d\n", 10 * a + b);

                return 0;
            }
        }
    }

    puts("[-] number doesn't exist");
}
