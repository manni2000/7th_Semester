#include <stdio.h>

int gcd(int a, int b) {
    if (a % b == 0)
        return b;
    return gcd(b, a % b);
}

int mulinv(int a, int m) {
    int ans = -1;
    if (gcd(a, m) != 1)
        return ans;
    for (int i = 1; i <= m; i++) {
        if (((a * i) - 1) % m == 0) {
            ans = i;
            break;
        }
    }
    return ans;
}

int main() {
    int x;
    int matrix[2][2];
    int adj[2][2];
    int m;

    printf("Enter your m value: ");
    scanf("%d", &m);
    
    printf("Enter your matrix values:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &x);
            matrix[i][j] = x;
        }
    }

    adj[0][0] = matrix[1][1];
    adj[0][1] = -matrix[1][0];
    adj[1][0] = -matrix[0][1];
    adj[1][1] = matrix[0][0];

    int det = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    printf("Determinant of matrix is %d\n", det);

    if (gcd(det, 26) != 1)
        printf("Can't find inverse, gcd is not equal to 1\n");
    else {
        int inverse = mulinv(det, 26);
        printf("%d is the inverse of det\n", inverse);
        
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                adj[i][j] *= inverse;
                int rem = (m - adj[i][j]) % m;
                adj[i][j] = rem;
            }
        }

        printf("Multiplicative inverse of matrix mod 26 is:\n");
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                printf("%d ", adj[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
