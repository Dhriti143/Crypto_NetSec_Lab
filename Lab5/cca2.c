#include <stdio.h>
#include <math.h>
#include <string.h>

// Function to find the greatest common divisor (GCD)
long gcd(long a, long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find extended GCD and modular inverse
long gcdExtended(long a, long b, long* x, long* y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    long x1, y1;
    long g = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;

    return g;
}

// Function to find modular inverse using extended Euclidean algorithm
long modInverse(long a, long m) {
    long x, y;
    if (gcdExtended(a, m, &x, &y) != 1) {
        printf("Inverse does not exist\n");
        return -1;
    }
    return (x % m + m) % m;
}

// Function to calculate modular exponentiation
long power(long x, unsigned long y, long p) {
    long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

// Function to encrypt a number
long encrypt(long message, long e, long n) {
    return power(message, e, n);
}

// Function to decrypt a number
long decrypt(long encrypted, long d, long n) {
    return power(encrypted, d, n);
}

int main() {
    long p, q;
    printf("Enter two prime numbers (p q): ");
    scanf("%ld %ld", &p, &q);

    long n = p * q; // Modulus
    long phi_n = (p - 1) * (q - 1); // Euler's totient function
    long e, d;

    // Finding e such that 1 < e < phi_n and gcd(e, phi_n) = 1
    for (e = 2; e < phi_n; e++) {
        if (gcd(e, phi_n) == 1) {
            break;
        }
    }

    printf("Public key (e, n): (%ld, %ld)\n", e, n);
    long m1,m2;
    printf("Enter number 1: ");
    scanf("%ld", &m1);
    printf("Enter number 2: ");
    scanf("%ld", &m2);
    
    long e1 = encrypt(m1, e, n);
    printf("Encrypted message: %ld\n", e1);
    long e2 = encrypt(m2, e, n);
    printf("Encrypted message: %ld\n", e2);
    e2 = e2*e1;

    // Calculating d
    d = modInverse(e, phi_n);
    printf("Private key: %ld\n", d);

    long m2_decrypt = decrypt(e2, d, n);
    printf("decryption of m2: %ld\n", m2_decrypt);

    long m1_decrypt = m2_decrypt/m2;
    printf("Thus, decryption of m1 is: %ld", m1_decrypt);

    return 0;
}
