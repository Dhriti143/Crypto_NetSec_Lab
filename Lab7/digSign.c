#include <stdio.h>
#include <string.h>
#include <math.h>

// Function to perform efficient exponentiation (a^b mod c)
int eff_exp(int a, int b, int c) {
    int x;
    int y = 0;
    int res = 1;
    while(b > 0) {
        if(b % 2 == 1) {
            res = (res * a) % c;
            res = res % c;
        }
        a = (a * a) % c;
        b = b / 2;
    }
    return res;
}

// Function to find modular inverse using extended Euclidean algorithm
int mod_inverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}

// Function to calculate ciphertext component 1 (c1)
int calculate_c1(int a, int k, int p) {
    return eff_exp(a, k, p);
}

// Function to calculate ciphertext component 2 (c2)
int calculate_c2(int b, int k, int m, int p) {
    int c3 = eff_exp(b, k, p);
    return (c3 * m) % p;
}

// Function to perform decryption
int verify_signature(int p, int a, int d_pub, int r, int s, int m) {
    int v1 = eff_exp(d_pub, r, p);
    int v2 = eff_exp(r, s, p);
    int v = (v1 * v2) % p;
    int u = eff_exp(a, m, p);
    return (v == u);
}

// Function to generate signature
int generate_signature(int p, int a, int d, int k, int m, int *r, int *s) {
    *r = eff_exp(a, k, p);
    int temp = mod_inverse(k, p - 1);
    *s = ((m - d * (*r)) * temp) % (p - 1);
    while(*s < 0) {
        *s = *s + (p - 1);
    }
    return 0;
}

int main() {
    int p = 71;
    int a = 7;
    int d = 16; // Private key
    int d_pub = eff_exp(a, d, p);
    printf("Public key (d_pub): %d\n", d_pub);
    int k = 31;
    int m = 15;
    int r, s;
    generate_signature(p, a, d, k, m, &r, &s);
    printf("Signature (r, s): (%d, %d)\n", r, s);

    if (verify_signature(p, a, d_pub, r, s, m)) {
        printf("Signature Verification Successful!\n");
    } else {
        printf("Signature Verification Failed!\n");
    }

    return 0;
}
