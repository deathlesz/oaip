#include <stdio.h>

int main() {
    int n;

    printf("enter number: ");
    scanf("%d", &n);

    switch (n) {
    case 0:
        puts("this is zero");
        break;
    case 1:
        puts("this is one");
        break;
    case 2:
        puts("this is two");
        break;
    case 3:
        puts("this is three");
        break;
    case 4:
        puts("this is four");
        break;
    case 5:
        puts("this is five");
        break;
    case 6:
        puts("this is six");
        break;
    case 7:
        puts("this is seven");
        break;
    case 8:
        puts("this is eight");
        break;
    case 9:
        puts("this is nine");
        break;
    case 10:
        puts("this is ten");
        break;
    default:
        puts("i don't know this number");
    }
}
