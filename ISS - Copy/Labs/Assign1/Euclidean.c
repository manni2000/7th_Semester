#include <stdio.h>

int gcd(int a, int b) {
    while (a % b != 0) {
        int temp = a;
        a = b;
        b = temp % b;
    }
    return b;
}

int main() {
    int a, b;
    printf("Enter two numbers for gcd\n");
    scanf("%d%d", &a, &b);
    printf("GCD using Euclidean Algorithm of %d and %d is %d\n", a, b, gcd(a, b));
    return 0;
}
