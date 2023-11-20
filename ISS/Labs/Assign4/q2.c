#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

#define BIT_MASK_8 255
#define BIT_MASK_16 65535
#define BIT_MASK_32 4294967295

uint32_t e, d, n;

uint32_t binpower(uint32_t a, uint32_t b, uint32_t m)
{
    a %= m;
    uint32_t res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (1LL * res * a) % m;
        a = (1LL * a * a) % m;
        b >>= 1;
    }
    return res;
}

int probablyPrimeFermat(uint32_t n, int iter)
{
    if (n < 4)
        return n == 2 || n == 3;

    for (int i = 0; i < iter; i++)
    {
        uint32_t a = 2 + random() % (n - 3);
        if (binpower(a, n - 1, n) != 1)
            return 0;
    }
    return 1;
}

uint32_t gcd(uint32_t a, uint32_t b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

// extended euclidean algorithm
uint32_t mygcd(uint32_t a, uint32_t b, uint32_t *x, uint32_t *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }
    uint32_t x1, y1;
    uint32_t d = mygcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - y1 * (a / b);
    return d;
}

uint32_t multiplicative_inverse(uint32_t a, uint32_t m)
{
    uint32_t x, y;
    uint32_t g = mygcd(a, m, &x, &y);
    if (g != 1)
    {
        return -1;
    }
    else
    {
        x = (x % m + m) % m;
        return x;
    }
}

void rsa_init()
{
    srand(time(NULL)); // to randomise results
    uint32_t p, q;
    while (1)
    {
        p = random() & BIT_MASK_8;
        q = random() & BIT_MASK_8;

        if (probablyPrimeFermat(p, 5) && probablyPrimeFermat(q, 5))
            break;
    }

    printf("P %" PRIu32 "\n", p);
    printf("Q %" PRIu32 "\n", q);

    n = p * q;
    uint32_t phi_n = (p - 1) * (q - 1);
    printf("N %" PRIu32 "\n", n);
    printf("Phi_N %" PRIu32 "\n", phi_n);

    while (1)
    {
        e = 2 + (random() % (phi_n - 2));
        if (gcd(phi_n, e) == 1)
            break;
    }
    printf("E %" PRIu32 "\n", e);

    d = multiplicative_inverse(e, phi_n);
    printf("D %" PRIu32 "\n", d);

    long long int t = (1LL * e * d) % phi_n;
    printf("Valid E & D if 1: %lld\n", t);
}

uint32_t rsa_encrypt(uint32_t data)
{
    return binpower(data, e, n);
}

uint32_t rsa_decrypt(uint32_t data)
{
    return binpower(data, d, n);
}

int main()
{
    rsa_init();

    uint32_t data = 89;
    uint32_t r = 3; // random number chosen by attacker
    printf("Data %" PRIu32 "\n", data);

    uint32_t enc = rsa_encrypt(data * r);
    printf("Encoded data %" PRIu32 "\n", enc);

    uint32_t dec = rsa_decrypt(enc);
    printf("Decoded data %" PRIu32 "\n", dec);

    uint32_t cracked_message = dec / r;
    printf("Cracked message %" PRIu32 "\n", cracked_message);

    return 0;
}
