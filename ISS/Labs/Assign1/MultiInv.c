#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, m;
    printf("Enter your a and m values:");
    scanf("%d%d", &a, &m);
    int ans = -1;

    for (int i = 1; i <= m; i++) {
        if (((a * i) - 1) % m == 0) {
            ans = i;
            break;
        }
    }

    printf("Multiplicative inverse of a mod m is %d\n", ans);

    return 0;
}
