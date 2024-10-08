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

    // Calculating d
    d = modInverse(e, phi_n);

    printf("Public key (e, n): (%ld, %ld)\n", e, n);
    printf("Private key (d, n): (%ld, %ld)\n", d, n);

    long message;
    printf("Enter number to encrypt: ");
    scanf("%ld", &message);

    long encrypted = encrypt(message, e, n);
    printf("Encrypted message: %ld\n", encrypted);

    long decrypted = decrypt(encrypted, d, n);
    printf("Decrypted message: %ld\n", decrypted);

    return 0;
}
