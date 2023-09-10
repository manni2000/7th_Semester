#include <stdio.h>

int main() {
    int a, m;
    printf("Enter your a and m values:");
    scanf("%d%d", &a, &m);
    int rem = (m - a) % m;
    printf("Additive inverse of a mod m is %d\n", rem);
    return 0;
}
